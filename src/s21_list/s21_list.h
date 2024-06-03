#ifndef S21_LIST
#define S21_LIST

#include <initializer_list>
#include <iostream>

namespace s21 {

template <class T>
class s21_list {
 private:
  struct Node {
    Node *next, *back;
    T arg;
  };

 public:
  class ListConstIterator;

  class ListIterator {
    friend class ListConstIterator;
    friend class s21_list;

   private:
    Node* node;

   public:
    ListIterator(Node*& other) : node(other){};
    ~ListIterator(){};

    T& operator*() { return node->arg; }
    ListIterator& operator++();
    ListIterator& operator--();
    ListIterator operator++(int);
    ListIterator operator--(int);
    bool operator!=(ListIterator it) { return node != it.node; };
    bool operator!=(ListConstIterator it) { return node != it.node; };
    bool operator==(ListIterator it) { return node == it.node; };
    bool operator==(ListConstIterator it) { return node == it.node; };
  };

  class ListConstIterator {
    friend class ListIterator;

   private:
    const Node* node;

   public:
    ListConstIterator(Node* const other) : node(other){};
    ListConstIterator(const ListIterator& other) : node(other.node){};
    ListConstIterator(ListIterator&& other) : node(other.node) {
      other.node = nullptr;
    };
    ~ListConstIterator(){};

    const T& operator*() { return node->arg; }
    bool operator!=(ListConstIterator it) { return node != it.node; };
    bool operator!=(ListIterator it) { return node != it.node; };
    bool operator==(ListIterator it) { return node == it.node; };
    bool operator==(ListConstIterator it) { return node == it.node; };
    ListConstIterator& operator++();
    ListConstIterator& operator--();
    ListConstIterator operator++(int);
    ListConstIterator operator--(int);
    ListConstIterator& operator=(const ListIterator& it);
  };

 private:
  Node* start;
  Node* finish;

 public:
  // List Member type
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = ListIterator;
  using const_iterator = ListConstIterator;
  using size_type = size_t;

  // List Functions
  s21_list();
  s21_list(size_type n);
  s21_list(std::initializer_list<value_type> const& items);
  s21_list(const s21_list& l);
  s21_list(s21_list&& l);
  ~s21_list();

  s21_list& operator=(s21_list&& l);

  // List Element access
  const_reference front() { return start->arg; }
  const_reference back() { return finish->back->arg; }

  // List Iterators
  iterator begin() { return iterator(start); };
  iterator end() { return iterator(finish); };
  const_iterator begin() const { return const_iterator(start); }
  const_iterator end() const { return const_iterator(finish); }

  // List Capacity
  bool empty() { return start == finish; };
  size_type size();
  /* (need more info)
  size_type max_size();
  */

  // List Modifiers
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference val);
  void push_front(const_reference value);
  void pop_back();
  void pop_front();
  void clear();
  void swap(s21_list& other);
  void merge(s21_list& other);
  void splice(const_iterator pos, s21_list& other);
  void reverse();
  void unique();
  void sort();
 
};

};  // namespace s21
#include "internal_class.tpp"
#include "s21_list.tpp"

#endif