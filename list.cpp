#include "napcoin.h"
#include <iostream>

List::List() {
  this->head = NULL;
  this->tail = NULL;
}

List::~List() {
  while (head != NULL) {
    Node *n = head->next;
    delete head;
    head = n;
  }
}

void List::append(Block *block) {
  Node *temp = new Node;
  temp->block = block;
  temp->next = NULL;
  if (head == NULL) {
    this->head = temp;
    this->tail = temp;
    temp = NULL;
  } else {
    this->tail->next = temp;
    this->tail = temp;
  }
}

Block *List::get_block(int index) {
  Node *temp_node = this->head;
  int counter = 0;
  while (temp_node != NULL) {
    if (index == counter) {
      break;
    }
    temp_node = temp_node->next;
    counter++;
  }
  return temp_node->block;
}
