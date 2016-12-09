#ifndef STACKHPP
#define STACKHPP

#include <iostream>
#include <iomanip>
#include <atomic>
#include <memory>
#include <vector>
#include <algorithm>
#include "deferred_allocator.h"

using namespace gcpp;

static deferred_heap heap;

template <class T>
class TopStack {
#define methods
#define params
#define structs
  
  private structs:
  struct Node {
    using defPtrNode = deferred_ptr<Node>;
    public methods:
    Node(const T &data)
    :_next(heap.make<defPtrNode>(nullptr)), _data(data) {}
    
    Node(defPtrNode &node, const T &data)
    :_next(node), _data(data) {}
    
    Node& operator=(const Node &copy) {
      if (*this != copy) {
        _next = copy._next;
        _data = copy._data;
      }
      return *this;
    }
    
    Node& operator=(Node &&copy) {
      _next = copy._next;
      _data = copy._data;
      copy._next = heap.make<defPtrNode>(nullptr);
      return *this;
    }
    
    private methods:
    Node() = delete;
    
    public params:
    defPtrNode _next;
    T _data;
  };
  
  using atomicNode = std::atomic<typename Node::defPtrNode>;
  
  public methods:
  bool tryPop(T &data) {
    typename Node::defPtrNode old_head = _head.load();
    if (old_head == nullptr) {
      return false;
    }
    while (old_head && !_head.compare_exchange_strong(old_head, old_head->_next));
    
    if (old_head == nullptr) {
      return false;
    }
    data = old_head->_data;
    shrinkToFit();
    return true;
  }
  
  void push(const T &data) {
  typename Node::defPtrNode new_head = heap.make<typename Node::defPtrNode>(new Node(data, _head.load()));
  
  while (!_head.compare_exchange_strong(new_head->next, new_head));
  }
  
  private methods:
  void shrinkToFit() {
    heap.collect();
  }
  
  private params:
  atomicNode _head;
};

#endif // STACKHPP
