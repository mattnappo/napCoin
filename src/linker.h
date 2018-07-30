#ifndef LINKER_H
#define LINKER_H

#include "json/json.hpp"

struct JsonNode {
  nlohmann::json *transaction;
  JsonNode *next;
};

class TransactionList {
public:
  JsonNode *head;
  JsonNode *tail;
  TransactionList();
  ~TransactionList();
  void append(nlohmann::json *transaction);
  nlohmann::json *get_transaction(int index, TransactionList *transaction_list);
};

#endif