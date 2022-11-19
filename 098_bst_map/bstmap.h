#include <cstdio>
#include <cstdlib>
#include <exception>
#include <iostream>

#include "map.h"

template<typename K, typename V>
class BstMap : public Map<K, V> {
 public:
  class Node {
   public:
    K key;
    V value;
    Node * left;
    Node * right;
    Node() : left(NULL), right(NULL){};
    Node(const K k, const V v) : key(k), value(v), left(NULL), right(NULL){};
  };

  Node * root;

 public:
  BstMap() : root(NULL){};
  BstMap(const BstMap & rhs) { root = copyHelper(rhs.root); }
  Node * copyHelper(const Node * other) {
    if (other == NULL) {
      return NULL;
    }
    else {
      Node * current = new Node(other->key, other->value);
      current->left = copyHelper(other->left);
      current->right = copyHelper(other->right);
      return current;
    }
  }

  BstMap & operator=(const BstMap & rhs) {
    BstMap temp(rhs);
    if (this != &rhs) {
      std::swap(root, temp.root);
    }
    return *this;
  }

  virtual ~BstMap() { destoryBST(root); }
  void destoryBST(Node * node) {
    if (node == NULL) {
      return;
    }
    destoryBST(node->left);
    destoryBST(node->right);
    delete node;
  }

  virtual void add(const K & key, const V & value) { root = addNode(root, key, value); }

  Node * addNode(Node * node, const K & key, const V & value) {
    if (node == NULL) {
      Node * toAdd = new Node(key, value);
      return toAdd;
    }
    if (node->key == key) {
      node->value = value;
      return node;
    }
    else if (node->key < key) {
      Node * newNode = addNode(node->right, key, value);
      node->right = newNode;
    }
    else {
      Node * newNode = addNode(node->left, key, value);
      node->left = newNode;
    }
    return node;
  }

  virtual const V & lookup(const K & key) const throw(std::invalid_argument) {
    Node * current = root;
    while (current != NULL) {
      if (current->key == key) {
        V * ans = &(current->value);
        return *ans;
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
        node->value = maxleft->value;
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
      std::cout << node->key << " ";
      printorder(node->right);
    }
  }
};
