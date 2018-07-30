#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include "json/json.hpp"
using json = nlohmann::json;

std::string hash_block(std::string contents); // Method that hashes the contents of each block
std::string get_timestamp();

struct JsonNode { // Add list templating eventually
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
  json get_transaction(int index);
  json get_transactions();
  void print_transactions();
};

class Block {
public:
  std::string this_hash; // Hash of the current block
  int index; // Index of the current block
  std::string timestamp; // Timestamp of the current block
	TransactionList *transactions; // List of transactions in the current block
  std::string previous_hash; // Hash of the previous block
  int proof_of_work;
  int init(int index, TransactionList *transactions, int proof_of_work, std::string previous_hash); // Initialize a new block
  int print_block(bool spacing); // Print the contents of the current block
};

struct Node { // For the list class
  Block *block;
  Node *next;
};

class List { // This is used to store the blocks
public:
  Node *head;
  Node *tail;
  List();
  ~List(); // Delete each item in the list
  void append(Block *block); // Append a block to the list
  Block *get_block(int index); // Get block by index (inefficient)
};

class Blockchain {
public:
  List *blocks = new List; // List of blocks in this chain
  int blockchain_size;
  Block *add_block(int index, TransactionList *transactions, int proof_of_work, std::string previous_hash);
  int export_blockchain(std::string blockchain_name); // Export blockchain to json file
  Block *create_genesis_block();
};

#endif
