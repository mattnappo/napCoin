#include "napcoin.h"
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

void TransactionList::append(json transaction) {
  JsonNode *temp = new JsonNode;
  temp->transaction = transaction;
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

json TransactionList::get_transaction(int index) {
  JsonNode *temp_node = this->head;
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

json TransactionList::get_transactions() {
  JsonNode *temp_node = this->head;
  json all_transactions; // this is a json array
  while (temp_node != NULL) {
    all_transactions.push_back(temp_node->transaction);
    temp_node = temp_node->next;
  }
  return all_transactions;
}
