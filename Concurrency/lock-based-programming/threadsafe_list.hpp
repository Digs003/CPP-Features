#pragma once
#include <memory>
#include <mutex>

template <typename T>
class threadsafe_list {
private:
  struct node {
    std::shared_ptr<T> data;
    std::unique_ptr<node> next;
    std::mutex m;
    node() : next(nullptr) {}
    node(const T &value) : data(std::make_shared<T>(value)), next(nullptr) {}
  };
  node head;

public:
  threadsafe_list() {}
  threadsafe_list(const threadsafe_list &other) = delete;
  threadsafe_list &operator=(const threadsafe_list &other) = delete;
  ~threadsafe_list() {
    remove_if([](const T &) { return true; });
  }

  void push_front(const T &value) {
    std::unique_ptr<node> new_node = std::make_unique<node>(value);
    std::lock_guard<std::mutex> lock(head.m);
    new_node->next = std::move(head.next);
    head.next = std::move(new_node);
  }

  template <typename Function> 
  void for_each(Function f) {
    node *current = &head;
    std::unique_lock<std::mutex> lock(current->m);
    while (const node *next = current->next.get()) {
      std::unique_lock<std::mutex> next_lock(next->m);
      lock.unlock();
      f(*next->data);
      current = next;
      lock = std::move(next_lock);
    }
  }

  template <typename Predicate>
  std::shared_ptr<T> find_first_if(Predicate p) {
    node *current = &head;
    std::unique_lock<std::mutex> lock(current->m);
    while (const node *next = current->next.get()) {
      std::unique_lock<std::mutex> next_lock(next->m);
      lock.unlock();
      if (p(*next->data)) {
        return next->data;
      }
      current = next;
      lock = std::move(next_lock);
    }
    return std::shared_ptr<T>();
  }

  template <typename Predicate>
  void remove_if(Predicate p) {
    node *current = &head;
    std::unique_lock<std::mutex> lock(current->m);
    while (const node *next = current->next.get()) {
      std::unique_lock<std::mutex> next_lock(next->m);
      if (p(*next->data)) {
        current->next = std::move(next->next);
        next_lock.unlock();
      } else {
        lock.unlock();
        current = next;
        lock = std::move(next_lock);
      }
    }
  }
};
