#include <memory>
#include <atomic>

template<typename T>
class lock_free_stack {
private:
  struct node {
    std::shared_ptr<T> data;
    node* next;
    node(const T& data_) : data(std::make_shared<T>(data_)), next(nullptr) {}
  };
  std::atomic<node*> head;
  std::atomic<unsigned> threads_in_pop;
  std::atomic<node*> to_be_deleted;

  void try_reclaim(node* old_head){
    if(threads_in_pop == 1) {
      node* nodes_to_delete = to_be_deleted.exchange(nullptr);
      if(--threads_in_pop == 0) {
        delete_nodes(nodes_to_delete);
      }
      else if(nodes_to_delete) {
        chain_pending_nodes(nodes_to_delete);
      }
    }
    else{
      chain_pending_node(old_head);
      --threads_in_pop;
    }
  }
  void chain_pending_nodes(node* nodes) {
    node* last = nodes;
    while(node* const next = last->next) {
      last = next;
    }
    chain_pending_nodes(nodes, last);
  }
  void chain_pending_nodes(node* first, node* last) {
    last->next = to_be_deleted.load();
    while(!to_be_deleted.compare_exchange_weak(last->next, first));
  }
  void chain_pending_node(node* n) {
    chain_pending_nodes(n, n);
  }
  void delete_nodes(node* nodes) {
    while(nodes) {
      node* next = nodes->next;
      delete nodes;
      nodes = next;
    }
  }
public:
  void push(const T& data) {
    node* new_node = new node(data);
    new_node->next = head.load();
    while(!head.compare_exchange_weak(new_node->next, new_node)) {}
  }
  // //This leaks the popped node and does not handle empty stack case
  // void pop(T& result) {
  //   node* old_head = head.load();
  //   while(!head.compare_exchange_weak(old_head, old_head->next)) {}
  //   result = old_head->data; // This might throw if T's copy constructor throws, leaking old_head
  // }
 
  //This also leaks but exception safe
  // std::shared_ptr<T> pop() {
  //   node* old_head = head.load();
  //   while(old_head && !head.compare_exchange_weak(old_head, old_head->next));
  //   return old_head ? old_head->data : std::shared_ptr<T>();
  // }
  
  std::shared_ptr<T> pop() {
    ++threads_in_pop;
    node* old_head = head.load();
    while(old_head && !head.compare_exchange_weak(old_head, old_head->next));
    std::shared_ptr<T> res;
    if(old_head) {
      res.swap(old_head->data);
    }
    try_reclaim(old_head);
    return res;
  }
};
