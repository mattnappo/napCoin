#ifndef LINKER_H
#define LINKER_H

#include <string>
#include <list>
#include <time.h>


#include "json/json.hpp"


using namespace std;
using json = nlohmann::json;



struct JsonNode { // For the list class
  Block *transaction;
  Node *next;
};

class TransactionList { // This is used to store the blocks
public:
  JsonNode *head;
  JsonNode *tail;
  TransactionList();
  ~TransactionList();
  void append(Block *block);
  Block *get_transaction(int index, TransactionList *list);
};

#endif
