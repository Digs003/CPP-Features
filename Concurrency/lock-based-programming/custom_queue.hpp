#include <memory>


template<typename T>
class queue {
private:
  struct node {
    T data;
    std::unique_ptr<node> next;

    node(T val) : data(std::move(val)) {}
  };
  std::unique_ptr<node> head;
  node* tail;
public:
  queue() {}
  queue(const queue& other) = delete;
  queue& operator=(const queue& other) = delete;

  std::shared_ptr<T> try_pop() {
    if(!head){
      return std::shared_ptr<T>();    
    }
    const std::shared_ptr<T> res(std::make_shared<T>(std::move(head->data)));
    std::unique_ptr<node> old_head = std::move(head);
    head = std::move(old_head->next);
    return res;
  }

  void push(T new_value) {
    std::unique_ptr<node> p(std::make_unique<node>(std::move(new_value)));
    const node* new_tail = p.get();
    if(tail){
      tail->next = std::move(p);
    } else{
      head = std::move(p);
    }
    tail = new_tail;
  }
};

//Adding dummy node because push() and try_pop() both access head->next when there is single element in queue
//as a result of that we gain no benefit of fine grain locking since both needs to be locked


template<typename T>
class queue_with_dummy {
private:
  struct node {
    std::shared_ptr<T> data;
    std::unique_ptr<node> next;    
  };
  std::unique_ptr<node> head;
  node* tail;
public:
  queue_with_dummy() : head(std::make_unique<node>()), tail(head.get()) {}
  queue_with_dummy(const queue_with_dummy& other) = delete;
  queue_with_dummy& operator=(const queue_with_dummy& other) = delete;

  std::shared_ptr<T> try_pop() {
    if(head.get() == tail){
      return std::shared_ptr<T>();
    }
    const std::shared_ptr<T> res = head->data;
    std::unique_ptr<node> old_head = std::move(head);
    head = std::move(old_head->next);
    return res;
  }
  void push(T new_value) {
    std::shared_ptr<T> new_data = std::make_shared<T>(std::move(new_value));
    std::unique_ptr<node> p = std::make_unique<node>();
    tail->data = new_data;
    const node* new_tail = p.get();
    tail->next = std::move(p);
    tail = new_tail;
  }
};
