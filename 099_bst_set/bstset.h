#include <cstdio>
#include <cstdlib>
#include <exception>
#include <iostream>

#include "set.h"

template<typename K>
class BstSet : public Set<K> {
 public:
  class Node {
   public:
    K key;
    Node * left;
    Node * right;
    Node() : left(NULL), right(NULL){};
    Node(const K k) : key(k), left(NULL), right(NULL){};
  };

  Node * root;

 public:
  BstSet() : root(NULL){};
  BstSet(const BstSet & rhs) { root = copyHelper(rhs.root); }
  Node * copyHelper(const Node * other) {
    if (other == NULL) {
      return NULL;
    }
    else {
      Node * current = new Node(other->key);
      current->left = copyHelper(other->left);
      current->right = copyHelper(other->right);
      return current;
    }
  }

  BstSet & operator=(const BstSet & rhs) {
    BstSet temp(rhs);
    if (this != &rhs) {
      std::swap(root, temp.root);
    }
    return *this;
  }

  virtual ~BstSet() { destoryBST(root); }
  void destoryBST(Node * node) {
    if (node == NULL) {
      return;
    }
    destoryBST(node->left);
    destoryBST(node->right);
    delete node;
  }

  virtual void add(const K & key) { root = addNode(root, key); }

  Node * addNode(Node * node, const K & key) {
    if (node == NULL) {
      Node * toAdd = new Node(key);
      return toAdd;
    }
    if (node->key == key) {
      return node;
    }
    else if (node->key < key) {
      Node * newNode = addNode(node->right, key);
      node->right = newNode;
    }
    else {
      Node * newNode = addNode(node->left, key);
      node->left = newNode;
    }
    return node;
  }

  virtual bool contains(const K & key) const throw(std::invalid_argument) {
    Node * current = root;
    while (current != NULL) {
      if (current->key == key) {
        return true;
      }
      else if (current->key < key) {
        current = current->right;
      }
      else {
        current = current->left;
      }
    }
    throw std::invalid_argument("Cannot find the key.\n");
  }

  virtual void remove(const K & key) { root = removeNode(root, key); }

  Node * removeNode(Node * node, const K & key) {
    if (node == NULL) {
      return NULL;
    }
    if (key < node->key) {
      node->left = removeNode(node->left, key);
    }
    else if (node->key < key) {
      node->right = removeNode(node->right, key);
    }
    else {
      if (node->left == NULL) {
        Node * res = node->right;
        delete node;
        return res;
      }
      else if (node->right == NULL) {
        Node * res = node->left;
        delete node;
        return res;
      }
      else {
        Node * maxleft = node->left;
        while (maxleft->right != NULL) {
          maxleft = maxleft->right;
        }
        node->key = maxleft->key;
        node->left = removeNode(node->left, maxleft->key);
      }
    }
    return node;
  }

  void printorder() { printorder(root); }

  void printorder(Node * node) {
    if (node == NULL)
      return;
    else {
      printorder(node->left);
      printorder(node->right);
      std::cout << node->key << " ";
    }
  }
};
