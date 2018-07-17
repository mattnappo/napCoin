#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <string>
#include <list>

using namespace std;

class Block {
private:
  string hash_block(string contents); // Method that hashes the contents of each block
  string get_timestamp(); // Method that returns a string of the current date and time
public:
  string this_hash; // Hash of the current block
  int index; // Index of the current block
  string timestamp; // Timestamp of the current block
	string data; // Data of the current block
  string previous_hash; // Hash of the previous block
  int init(int index, string data, string previous_hash,
    bool from_import = false, string timestamp = "", string this_hash = ""); // Initialize a block
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
  Block *get_block(int index, List *list); // Get block by index (inefficient)
};

class Blockchain {
private:
  clock_t tStart = clock(); // Used to calculate the build time of the blocks
  Block *head_block = new Block;
  Block *build_genesis();
  Block *next_block(Block *last_block); // Add a block to the list (and the blockchain itself)
  int check(Block block_1, Block block_2); // Validate two blocks in the chain
  int validate(); // Validate the entire blockchain
  Block *genesis();
public:
  int blockchain_size; // Amount of blocks in the chain
  List *blocks = new List; // List of blocks in this chain
  int build(int blockchain_size, bool show_blocks); // Build blocks
  int export_blockchain(string blockchain_name); // Export blockchain to json file
  int import_blockchain(string blockchain_name, bool show_blocks); // Import blockchain from json file
};

#endif
