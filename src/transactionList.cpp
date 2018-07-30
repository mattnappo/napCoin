#include "linker.h"
#include "json/json.hpp"

using json = nlohmann::json;

TransactionList::TransactionList() {
  this->head = NULL;
  this->tail = NULL;
}

TransactionList::~TransactionList() {
  while (head != NULL) {
    JsonNode *n = head->next;
    delete head;
    head = n;
  }
}

void TransactionList::append(json *transactions) {
  JsonNode *temp = new JsonNode;
  temp->transactions = transactions;
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

json *List::get_transaction(int index, TransactionList *transaction_list) {
  JsonNode *temp_node = list->head;
  int counter = 0;
  while (temp_node != NULL) {
    if (index == counter) {
      break;
    }
    temp_node = temp_node->next;
    counter++;
  }
  return temp_node->transaction;
}
