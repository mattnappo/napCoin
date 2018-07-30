#ifndef LINKER_H
#define LINKER_H

#include "json/json.hpp"
using json = nlohmann::json;

struct JsonNode {
  json transaction;
  JsonNode *next;
};

class TransactionList {
public:
  JsonNode *head;
  JsonNode *tail;
  TransactionList();
  ~TransactionList();
  void append(json transaction);
  json get_transaction(int index, TransactionList *transaction_list);
  void print_transactions();
};

#endif