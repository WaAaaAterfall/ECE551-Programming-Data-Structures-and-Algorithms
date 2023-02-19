#include "node.h"

void Node::buildMap(BitString b, std::map<unsigned, BitString> & theMap) {
  //WRITE ME!
  if (sym != NO_SYM) {
    assert(left == NULL && right == NULL);
    theMap[sym] = b;
  }
  else {
    if (left != NULL) {
      left->buildMap(b.plusZero(), theMap);
    }
    if (right != NULL) {
      right->buildMap(b.plusOne(), theMap);
    }
  }
}
