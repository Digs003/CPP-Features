#include <atomic>
#include <memory>
#include "hazard_pointer.hpp"



template <typename T> class lock_free_stack {
private:
  struct node {
    std::shared_ptr<T> data;
    node *next;
    node(const T &data_) : data(std::make_shared<T>(data_)), next(nullptr) {}
  };
  struct data_to_reclaim {
    node* data;
    data_to_reclaim* next;
    data_to_reclaim(T* p): data(p), next(nullptr) {}
    ~data_to_reclaim() {
      delete data;
    }
  };
  std::atomic<data_to_reclaim*> nodes_to_reclaim;
  std::atomic<node *> head;
  bool outstanding_hazard_pointers_for(node *p) {
    for (unsigned i = 0; i < max_hazard_pointers; ++i) {
      if (hazard_pointers[i].pointer.load() == p) {
        return true;
      }
    }
    return false;
  }
  void add_to_reclaim_list(data_to_reclaim* node) {
    node->next = nodes_to_reclaim.load();
    while(!nodes_to_reclaim.compare_exchange_weak(node->next, node));
  }
  void reclaim_later(node *data) {
    add_to_reclaim_list(new data_to_reclaim(data));
  }
  void delete_nodes_with_no_hazards() {
    data_to_reclaim* current = nodes_to_reclaim.exchange(nullptr);
    while(current) {
      data_to_reclaim* const next = current->next;
      if(!outstanding_hazard_pointers_for(current->data)) {
        delete current;
      }
      else{
        add_to_reclaim_list(current);
      }
      current = next;
    }
  }
public:
  void push(const T &data) {
    node *new_node = new node(data);
    new_node->next = head.load();
    while (!head.compare_exchange_weak(new_node->next, new_node)) {
    }
  }
  std::shared_ptr<T> pop() {
    std::atomic<void *> &hp = get_hazard_pointer_for_current_thread();
    node *old_head = head.load();
    do{
      node* temp;
      do{
        temp = old_head;
        hp.store(old_head);
        old_head = head.load();
      }while(old_head != temp);

    }while (old_head && !head.compare_exchange_strong(old_head, old_head->next));
    hp.store(nullptr);
    std::shared_ptr<T> res;
    if(old_head) {
      res.swap(old_head->data);
      if(outstanding_hazard_pointers_for(old_head)) {
        reclaim_later(old_head);
      }
      else{
        delete old_head;
      }
      delete_nodes_with_no_hazards();
    }
    return res;
  }
};
