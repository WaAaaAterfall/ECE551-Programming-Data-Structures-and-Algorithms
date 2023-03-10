#ifndef __LL_HPP__
#define __LL_HPP__

#include <assert.h>

#include <cstdlib>
#include <exception>
#include <iostream>

//YOUR CODE GOES HERE
class myException : public std::exception {
 public:
  virtual const char * what() const throw() {
    return "The requested item does not exist.\n";
  }
};

template<typename T>
class LinkedList {
  class Node {
   public:
    T data;
    Node * next;
    Node * prev;
    Node() : next(NULL), prev(NULL){};
    Node(const T & data, Node * n, Node * p) : data(data), next(n), prev(p){};
  };

 public:
  Node * head;
  Node * tail;
  int size;

  LinkedList() : head(NULL), tail(NULL), size(0){};
  LinkedList(const LinkedList & rhs);
  LinkedList & operator=(const LinkedList & rhs);
  ~LinkedList();
  void addFront(const T & item);
  void addBack(const T & item);
  bool remove(const T & item);
  T & operator[](int index);
  const T & operator[](int index) const;
  int find(const T & item) const;
  int getSize() const;
};

template<typename T>
LinkedList<T>::LinkedList(const LinkedList & rhs) {
  Node * rhsCurrent = rhs.head;
  head = new Node(rhs.head->data, NULL, NULL);
  rhsCurrent = rhsCurrent->next;
  while (rhsCurrent != NULL) {
    addBack(rhsCurrent->data);
    rhsCurrent = rhsCurrent->next;
  }
}

template<typename T>
LinkedList<T> & LinkedList<T>::operator=(const LinkedList & rhs) {
  LinkedList * newLL = new LinkedList(rhs);
  std::swap(newLL->head, head);
  std::swap(newLL->tail, tail);
  std::swap(newLL->size, size);
  delete newLL;
}

template<typename T>
void LinkedList<T>::addFront(const T & item) {
  Node * newN = new Node(item, head, NULL);
  head->prev = newN;
  head = newN;
  size++;
}

template<typename T>
void LinkedList<T>::addBack(const T & item) {
  Node * newN = new Node(item, NULL, tail);
  tail->next = newN;
  tail = newN;
  size++;
}

template<typename T>
bool LinkedList<T>::remove(const T & item) {
  Node * current = head;
  while (current != NULL) {
    if (current->data == item) {
      if (current->prev == NULL) {
        head = current->next;
        head->prev = NULL;
        delete current;
      }
      else if (current->next == NULL) {
        tail = current->prev;
        tail->next = NULL;
        delete current;
      }
      else {
        current->prev->next = current->next;
        current->next->prev = current->prev;
        delete current;
      }
      size--;
      return true;
    }
  }
  return false;
}

template<typename T>
T & LinkedList<T>::operator[](int index) {
  int count = 0;
  Node * current = head;
  while (count < index) {
    current = current->next;
    count++;
    if (current == NULL) {
      throw myException();
    }
  }
  return current->data;
}

template<typename T>
const T & LinkedList<T>::operator[](int index) const {
  int count = 0;
  if (index >= size) {
    exit(EXIT_FAILURE);
  }
  Node * current = head;
  while (count < index) {
    current = current->next;
  }
  return current->data;
}

template<typename T>
int LinkedList<T>::find(const T & item) const {
  int count = 0;
  Node * current = head;
  while (count < size) {
    if (current->data == item) {
      return count;
    }
  }
  return -1;
}

template<typename T>
int LinkedList<T>::getSize() const {
  return size;
}

template<typename T>
LinkedList<T>::~LinkedList<T>() {
  Node * node = head;
  while (node != NULL) {
    Node * toDelete = node;
    node = node->next;
    delete toDelete;
  }
  head = NULL;
  tail = NULL;
  size = 0;
}
#endif
