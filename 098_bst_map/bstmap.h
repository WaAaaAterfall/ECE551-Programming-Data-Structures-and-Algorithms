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
  BstMap(const BstMap & rhs) { copyHelper(root, rhs.root); }
  void copyHelper(Node * current, const Node * other) {
    if (other == NULL) {
      current = NULL;
    }
    else {
      current = new Node(other->key, other->value);
      copyHelper(current->left, other->left);
      copyHelper(current->right, current->right);
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

  virtual void add(const K & key, const V & value) {
    if (root == NULL) {
      Node * newNode = new Node(key, value);
      root = newNode;
    }
    root = addNode(root, key, value);
  }
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

  virtual void remove(const K & key) {
    Node * current = root;
    if (current == NULL) {
      return;
    }
    while (current != NULL) {
      if (key < current->key) {
        if (current->left != NULL && current->left->key == key) {
          current->left = removeNode(current->left);
        }
        else {
          current = current->left;
        }
      }
      else {
        if (current->right != NULL && current->right->key == key) {
          current->right = removeNode(current->right);
        }
        else {
          current = current->right;
        }
      }
    }
  }

  Node * removeNode(Node * node) {
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
      Node * right = node->right;
      Node * leftMost;
      if (node->left->right == NULL) {
        leftMost = node->left;
      }
      else {
        Node * curr = node->left;
        while (curr->right != NULL) {
          curr = curr->right;
        }
        leftMost = curr;
      }
      leftMost->right = right;
      delete node;
      return leftMost->left;
    }
  }
};
