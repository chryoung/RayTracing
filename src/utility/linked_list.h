#ifndef D4F5B7F5_8A00_45A1_B7EB_99B4792C6C8F
#define D4F5B7F5_8A00_45A1_B7EB_99B4792C6C8F

#include <stdexcept>

template<class T>
class LinkedListNode {
public:
  LinkedListNode<T>(T v): val(v) {}
  T val;
  LinkedListNode* next;
};

template<class T>
class LinkedList {
public:
  LinkedList<T>(): _head(new LinkedListNode<T>(T{})), _tail(_head) {}
  ~LinkedList<T>() {
    free_list();
  }

  LinkedList<T>(const LinkedList&) = delete;
  LinkedList<T> operator=(const LinkedList&) = delete;
  LinkedList<T>(LinkedList&& orig) {
    _head = orig._head;
    _tail = orig._tail;

    orig._head = nullptr;
    orig._tail = nullptr;
  }

  LinkedList<T> operator=(LinkedList&& orig) {
    free_list();
    _head = orig._head;
    _tail = orig._tail;

    orig._head = nullptr;
    orig._tail = nullptr;
  }

  bool is_empty() {
    return _head == _tail || _head == nullptr || _head->next == nullptr;
  }

  void add_back(LinkedListNode<T>* v) {
    _tail->next = v;
    _tail = v;
  }

  LinkedListNode<T>* pop_front() {
    if (_head == nullptr || _head->next == nullptr || _head == _tail) {
      throw std::out_of_range("Linked list is empty.");
    }

    LinkedListNode<T>* n = _head->next;
    _head->next = n->next;

    return n;
  }

private:
  void free_list() {
    LinkedListNode<T>* iter = _head;
    LinkedListNode<T>* next;
    while (iter) {
      next = iter->next;
      delete iter;
      iter = next;
    }

    _head = nullptr;
    _tail = nullptr;
  }

  LinkedListNode<T>* _head;
  LinkedListNode<T>* _tail;
};

#endif