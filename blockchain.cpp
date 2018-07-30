#include "main.h"
#include <string>
#include <fstream>
#include <iostream>
#include "json/json.hpp"
#include "argon2/argon2.h"
using json = nlohmann::json;
using namespace std;

string get_timestamp() {
  time_t t = time(0);
  tm* now = localtime(&t);
  string year = to_string((now->tm_year + 1900));
  string month = to_string((now->tm_mon + 1));
  string day = to_string(now->tm_mday);
  string hour = to_string(now->tm_hour);
  string min = to_string(now->tm_min);
  string sec = to_string(now->tm_sec);
  string c_time = year + "-" + month + "-" + day + " @ " + hour + ":" + min + ":" + sec;
  return c_time;
}

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

Block *Blockchain::create_genesis_block() {
    Block *head_block = new Block;
    head_block->init(0, NULL, 9, "0");
    this->blocks->append(head_block);
    return head_block;
}

Block *Blockchain::add_block(int index, TransactionList *transactions, int proof_of_work, string previous_hash) {
    Block *new_block = new Block;
    new_block->init(index, transactions, proof_of_work, previous_hash);
    this->blocks->append(new_block);
    return new_block;
}

int Blockchain::export_blockchain(string blockchain_name) {
    json blockchain;
    blockchain["blocks"] = { };
    for (int i = 0; i < this->blockchain_size + 1; i++) {
        blockchain["blocks"][i] = { };
        Block *block = this->blocks->get_block(i);
        blockchain["blocks"][i]["index"] = block->index;
        blockchain["blocks"][i]["timestamp"] = block->timestamp;
        blockchain["blocks"][i]["transactions"] = block->transactions->get_transactions();
        blockchain["blocks"][i]["previous_hash"] = block->previous_hash;
        blockchain["blocks"][i]["hash"] = block->this_hash;
    }
    string filename = blockchain_name + ".json";
    ofstream o(filename);
    o << setw(4) << blockchain << endl;
    o.close();
    cout << "\033[0;32mCurrent blockchain exported to \033[1;32m" << filename << ".\033[0m" << endl;
    return 0;
}