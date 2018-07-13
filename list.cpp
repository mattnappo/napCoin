#include "blockchain.h"

Node *head;
List::List() {
  head = NULL;
}
List::~List() {
  while (head != NULL) {
    Node *n = head->next;
    delete head;
    head = n;
  }
}
void List::append(Block *block) {
  if (this->head == NULL) {
    this->head = new Node;
    this->head->block = block;
    this->head->next = NULL;
    return;
  }
  Node *current_node = this->head;
  while (current_node->next != NULL) {
    current_node = current_node->next;
  }
  Node *new_node = new Node;
  new_node->block = block;
  new_node->next = NULL;
  current_node->next = new_node;
}
Block *List::get_block(int index, List *list) {
  Node *temp_node = list->head;
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
