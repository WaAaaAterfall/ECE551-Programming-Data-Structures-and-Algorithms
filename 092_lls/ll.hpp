#ifndef __LL_HPP__
#define __LL_HPP__

#include <assert.h>

#include <cstdlib>
#include <exception>
#include <iostream>
template<typename T>

//YOUR CODE GOES HERE
class LinkedList {
 public:
  class Node {
   public:
    T data;
    Node * next;
    Node * prev;
    Node() : data(0), next(NULL), prev(NULL){};
    Node(const T & data, Node * n, Node * p) : data(data), next(n), prev(p){};
  };

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

class myException : public std::exception {
 public:
  virtual const char * what() const throw() {
    return "The requested item does not exist.\n";
  }
};

template<typename T>
//copy constructor
LinkedList<T>::LinkedList(const LinkedList & rhs) {
  Node * current = rhs.head;
  head = NULL;
  tail = NULL;
  size = 0;
  while (current != NULL) {
    addBack(current->data);
    current = current->next;
  }
}

template<typename T>
//assignment copy
LinkedList<T> & LinkedList<T>::operator=(const LinkedList & rhs) {
  if (this != &rhs) {
    LinkedList<T> temp = LinkedList<T>(rhs);
    std::swap(temp.head, head);
    std::swap(temp.tail, tail);
    std::swap(temp.size, size);
  }
  return *this;
}

template<typename T>
LinkedList<T>::~LinkedList() {
  while (tail != NULL) {
    Node * current = tail->prev;
    delete tail;
    tail = current;
  }
  size = 0;
  head = NULL;
}

template<typename T>
void LinkedList<T>::addFront(const T & item) {
  Node * add = new Node(item, head, NULL);
  if (head != NULL) {
    head->prev = add;
  }
  else {
    tail = add;
  }
  head = add;
  size++;
}

template<typename T>
void LinkedList<T>::addBack(const T & item) {
  Node * add = new Node(item, NULL, tail);
  if (tail != NULL) {
    tail->next = add;
  }
  else {
    head = add;
  }
  tail = add;
  size++;
}

template<typename T>
bool LinkedList<T>::remove(const T & item) {
  Node * current = head;
  if (current == NULL) {
    return false;
  }
  while (current != NULL) {
    if (current->data == item) {
      if (current->prev == NULL) {
        head = current->next;
      }
      else {
        current->prev->next = current->next;
      }
      if (current->next == NULL) {
        tail = current->prev;
      }
      else {
        current->next->prev = current->prev;
      }
      size--;
      delete current;
      return true;
    }
    current = current->next;
  }
  return false;
}

template<typename T>
T & LinkedList<T>::operator[](int index) {
  int i = 0;
  Node * current = head;
  while (i < index) {
    current = current->next;
    i++;
    if (current == NULL) {
      throw myException();
    }
  }
  return current->data;
}

template<typename T>
const T & LinkedList<T>::operator[](int index) const {
  int i = 0;
  Node * current = head;
  while (i < index) {
    current = current->next;
    i++;
    if (current == NULL) {
      throw myException();
    }
  }
  return current->data;
}

template<typename T>
int LinkedList<T>::find(const T & item) const {
  Node * current = head;
  int index = 0;
  while (current != NULL) {
    if (current->data == item) {
      return index;
    }
    current = current->next;
    index++;
  }
  return -1;
}

template<typename T>
int LinkedList<T>::getSize() const {
  return size;
}
#endif
