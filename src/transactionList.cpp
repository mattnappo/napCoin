#include "linker.h"
TransactionList::TransactionList() {
  this->head = NULL;
  this->tail = NULL;
}

TransactionList::~TransactionList() {
  while (head != NULL) {
    Node *n = head->next;
    delete head;
    head = n;
  }
}

void TransactionList::append(Block *block) {
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