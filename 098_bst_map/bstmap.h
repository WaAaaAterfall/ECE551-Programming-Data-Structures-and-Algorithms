#include <cstdlib>
#include <exception>

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
  BstMap & operator=(const BstMap & rhs);
  virtual void add(const K & key, const V & value) {
    if (root == NULL) {
      Node * newNode = new Node(key, value);
      root = newNode;
    }
    root = addNode(root, key, value);
  }
  virtual const V & lookup(const K & key) const throw(std::invalid_argument);
  virtual void remove(const K & key);
  virtual ~BstMap();
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
  void destoryBST(Node * toDestory);
};

template<typename K, typename V>
BstMap<K, V> & BstMap<K, V>::operator=(const BstMap & rhs) {
  BstMap<K, V> temp(rhs);
  if (this != &rhs) {
    std::swap(root, temp.root);
  }
  return *this;
}

template<typename K, typename V>
BstMap<K, V>::~BstMap() {
  destoryBST(root);
}

template<typename K, typename V>
const V & BstMap<K, V>::lookup(const K & key) const throw(std::invalid_argument) {
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

template<typename K, typename V>
void BstMap<K, V>::destoryBST(Node * toDestory) {
  if (toDestory == NULL) {
    return;
  }
  destoryBST(toDestory->left);
  destoryBST(toDestory->right);
  toDestory->left = NULL;
  toDestory->right = NULL;
  delete toDestory;
}

template<typename K, typename V>
void BstMap<K, V>::remove(const K & key) {
  Node ** current = &root;
  while (*current != NULL) {
    if (key == (*current)->key) {
      if ((*current)->left == NULL) {
        Node * toDelete = *current;
        *current = (*current)->right;
        delete toDelete;
      }
      else if ((*current)->right == NULL) {
        Node * toDelete = *current;
        *current = (*current)->left;
        delete toDelete;
      }
      else {
        Node ** leftMost = &((*current)->left);
        while ((*leftMost)->right != NULL) {
          leftMost = &(*leftMost)->right;
        }
        Node * left = (*leftMost)->left;
        (*leftMost)->left = (*current)->left;
        (*leftMost)->right = (*current)->right;
        Node * toDelete = *current;
        *current = *leftMost;
        *leftMost = left;
        delete toDelete;
      }
    }
    else if ((*current)->key < key) {
      current = &((*current)->right);
    }
    else {
      current = &((*current)->left);
    }
  }
}
