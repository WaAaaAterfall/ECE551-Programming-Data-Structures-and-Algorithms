#include <assert.h>

#include <cstdlib>
#include <iostream>

#include "il.hpp"

class Tester {
 public:
  // testing for default constructor is done for you
  void testDefCtor() {
    IntList il;
    assert(il.head == NULL);
    assert(il.tail == NULL);
    assert(il.getSize() == 0);
  }
  // example of another method you might want to write
  void testAddFront() {
    // WRITE ME
    IntList il;
    il.addFront(1);
    assert(&il != NULL && il.head != NULL && il.tail != NULL);
    assert(il.getSize() == 1);
    assert(il.head->data == 1);
    assert(il.tail->data == 1);
    assert(il.head->next == NULL);
    assert(il.head->prev == NULL);
    assert(il.tail->next == NULL);
    assert(il.tail->prev == NULL);
    assert(il.head == il.tail);
    il.addFront(3);
    assert(il.getSize() == 2);
    assert(il.head != NULL);
    assert(il.head->data == 3 && il.tail->data == 1);
    assert(il.head->next == il.tail && il.head->prev == NULL);
    assert(il.tail->next == NULL && il.tail->prev == il.head);
  }

  // many more tester methods
  //test add back
  void testAddBack() {
    IntList il;
    il.addBack(1);
    assert(&il != NULL && il.head != NULL && il.tail != NULL);
    assert(il.getSize() == 1);
    assert(il.head != NULL);
    assert(il.head->prev == NULL);
    assert(il.head->data == 1 && il.tail->data == 1);
    assert(il.head->next == NULL && il.head->prev == NULL);
    assert(il.head == il.tail);
    il.addBack(2);
    assert(il.getSize() == 2);
    assert(il.head != NULL && il.head->prev == NULL);
    assert(il.head->data == 1);
    assert(il.head->next = il.tail);
    assert(il.tail->data == 2);
    assert(il.tail->next == NULL && il.tail->prev == il.head);
  }

  //Test copy constructor
  void testCopyConstructor() {
    IntList * il = new IntList();
    il->addFront(2);
    il->addBack(3);  //2 3
    IntList * copy = new IntList(*il);
    assert(copy->getSize() == 2);
    assert(copy->head->prev == NULL);
    assert(copy->head->data == 2);
    assert(copy->head->next = copy->tail);
    assert(copy->tail->data == 3);
    assert(copy->tail->next == NULL);
    assert(copy->tail->prev == copy->head);
    assert(il->head != copy->head && il->tail != copy->tail);
    delete il;
    assert(copy->getSize() == 2);
    IntList * copy2 = new IntList(*copy);
    delete copy;
    copy2->addBack(1);
    assert(copy2->getSize() == 3);
    delete copy2;
  }

  //assignment copy
  void testCopyAssignment() {
    IntList * il = new IntList();
    il->addFront(2);
    il->addBack(3);  //2 3
    IntList copy;
    copy.addFront(2);
    copy = *il;
    assert(copy.getSize() == 2);
    assert(copy.head != NULL && copy.head->prev == NULL);
    assert(copy.head->data == 2);
    assert(copy.head->next == copy.tail);
    assert(copy.tail->data == 3);
    assert(copy.tail->next == NULL && copy.tail->prev == copy.head);
    assert(il->head != copy.head);
    assert(il->tail != copy.tail);
    copy.addBack(10);
    assert(il->find(10) == -1);
    delete (il);
    assert(copy.getSize() == 3);
    IntList copy2 = copy;
    copy2.addBack(10);
    assert(copy2.getSize() == 4 && copy.getSize() == 3);
  }

  void testUnsuccessRemove() {
    IntList il;
    il.addFront(1);
    il.addBack(2);
    il.addFront(300);
    il.addBack(4);  //300 1 2 4
    assert(il.remove(200) == false);
    assert(il.getSize() == 4);
    assert(il.head->data == 300 && il.head->next->data == 1 &&
           il.head->next->next->data == 2);
    assert(il.head->next->next->next->data == 4);
    assert(il.head->next->next->next->next == NULL);
    assert(il.tail->data =
               4 && il.tail->prev->data == 2 && il.tail->prev->prev->data == 1);
    assert(il.tail->prev->prev->prev->data == 300);
    assert(il.tail->prev->prev->prev->prev == NULL);
    assert(il.find(200) == -1);
  }

  void testRemove() {
    IntList l1;
    l1.addBack(3);
    IntList::Node * n1 = l1.head;
    l1.addBack(2);
    IntList::Node * n2 = l1.tail;
    l1.addBack(1);
    IntList::Node * n3 = l1.tail;
    l1.addBack(4);  //3 2 1 4
    IntList::Node * n4 = l1.tail;
    //test delete tail
    assert(l1.remove(4));  //3 2 1
    assert(!l1.remove(0));
    assert(l1.head == n1);
    assert(l1.tail == n3);
    assert(l1[0] == 3 && l1[1] == 2 && l1[2] == 1);
    assert(l1.getSize() == 3);
    //n1
    assert(n1->next == n2);
    assert(n1->prev == NULL);
    assert(n1->data = 3);
    //n2
    assert(n2->data = 2);
    assert(n2->next == n3);
    assert(n2->prev == n1);
    //n3
    assert(n3->data = 1);
    assert(n3->next == NULL);
    assert(n3->prev == n2);
    //test delete front
    assert(l1.remove(3));  //2 1
    assert(l1.head == n2);
    assert(l1.tail == n3);
    assert(l1.head->next == l1.tail && l1.head == l1.tail->prev);
    assert(l1.getSize() == 2);
    //n2
    assert(n2->next == n3);
    assert(n2->prev == NULL);
    assert(n2->data == 2);
    //n3
    assert(n3->data == 1);
    assert(n3->next == NULL);
    assert(n3->prev == n2);
    assert(l1[0] == 2 && l1[1] == 1);
    //test delete in the middle
    l1.addBack(1);  // 2 1 1 n2 n3 n5
    IntList::Node * n5 = l1.tail;
    assert(l1.remove(1));  //2 1 n2 n3
    assert(l1[0] == 2 && l1[1] == 1);
    assert(n2->data == 2 && n2->next == n5 && n2->prev == NULL);
    assert(n5->data == 1 && n5->next == NULL && n5->prev == n2);
    //delete rest of the list
    assert(l1.remove(1));
    assert(n2 == l1.head && n2 == l1.tail);
    assert(l1[0] == 2);
    assert(l1.getSize() == 1);
    assert(l1.head->next == NULL && l1.head->prev == NULL);
    assert(l1.remove(2));
    assert(l1.head == NULL && l1.tail == NULL);
    assert(l1.remove(1) == false);
  }

  //test rule of three
  void testRuleOfThree() {
    IntList * il1 = new IntList();
    il1->addBack(3);
    il1->addFront(2);               //2 3
    IntList * il2 = new IntList();  //assignment
    *il2 = *il1;
    il1->addBack(5);
    il1->addFront(4);
    il1->remove(3);
    assert(il1->getSize() == 3);
    assert(il2->head->data == 2 && il2->tail->data == 3 && il2->getSize() == 2);
    il2->addBack(6);
    il2->addFront(7);
    il2->remove(3);
    assert(il1->getSize() == 3 && il1->head->data == 4);
    assert(il2->head->data == 7 && il2->tail->data == 6 && il2->getSize() == 3);
    IntList * il3 = new IntList(*il1);  //copy constroctor
    assert(il3->head->data == 4 && il3->tail->data == 5 && il3->getSize() == 3);
    delete il1;
    assert(il2 != NULL && il3 != NULL);
    IntList il4;
    il4.addBack(10);
    il4.addFront(11);
    IntList il5 = il4;
    assert(il5.head->data == 11 && il5.tail->data == 10 && il5.getSize() == 2);
    delete il2;
    delete il3;
  }
};

int main(void) {
  Tester t;
  t.testDefCtor();
  std::cout << "DefCtor Correct"
            << "\n";
  t.testAddFront();
  std::cout << "Add Front Correct"
            << "\n";
  t.testAddBack();
  std::cout << "Add Back Correct"
            << "\n";
  t.testRuleOfThree();
  std::cout << "Rule of Three Correct"
            << "\n";
  t.testCopyAssignment();
  std::cout << "Copy Assign Correct"
            << "\n";
  t.testCopyConstructor();
  std::cout << "Copy constructor Correct"
            << "\n";
  t.testRemove();
  std::cout << "Copy remove Correct"
            << "\n";
  t.testUnsuccessRemove();
  std::cout << "unsuccessful Copy constructor Correct"
            << "\n";
  // write calls to your other test methods here
  std::cout << "All Correct"
            << "\n";
  return EXIT_SUCCESS;
}
