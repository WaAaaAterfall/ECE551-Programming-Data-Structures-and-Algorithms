#include "node.h"

Node * buildTree(uint64_t * counts) {
  //WRITE ME!
  priority_queue_t priotoryQueue;
  for (size_t i = 0; i < 257; i++) {
    if (counts[i] != 0) {
      Node * newNode = new Node(i, counts[i]);
      priotoryQueue.push(newNode);
    }
  }
  while (priotoryQueue.size() > 1) {
    Node * first = priotoryQueue.top();
    priotoryQueue.pop();
    Node * second = priotoryQueue.top();
    priotoryQueue.pop();
    Node * merge = new Node(first, second);
    priotoryQueue.push(merge);
  }
  return priotoryQueue.top();
}
