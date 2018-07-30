#include "main.h"
#include "json/json.hpp"
#include "argon2/argon2.h"
#include <iostream>

using namespace std;

int Block::init(int index, TransactionList *transactions, int proof_of_work, string previous_hash) {
  this->index = index;
  this->transactions = transactions;
  this->proof_of_work = proof_of_work;
  this->previous_hash = previous_hash;
  this->timestamp = get_timestamp();
  
  json raw = this->transactions->get_transactions();
  string t_string = raw.dump();

  string contents = to_string(this->index) + this->timestamp + t_string + this->previous_hash;
  this->this_hash = hash_block(contents);

  return 0;
}

int Block::print_block(bool spacing) {
  if (spacing) { cout << endl; }
  cout << "Previous block: " << this->previous_hash << endl;
  cout << "Index:          " << this->index << endl;
  cout << "Timestamp:      " << this->timestamp << endl;
  cout << "Transactions:   " << this->transactions << endl;
  cout << "Hash:           " << this->this_hash << endl;
  if (spacing) { cout << endl; }
  return 0;
}
