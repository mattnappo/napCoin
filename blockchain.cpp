#include "blockchain.h"
#include "json/json.hpp"

#include <iostream>
#include <fstream>

using namespace std;
using json = nlohmann::json;

clock_t tStart = clock();
Block *head_block = new Block;
Block *Blockchain::add_block(Block last_block) {
  Block *new_block = new Block;
  int index = last_block.block_index + 1;
  new_block->init(index, "This is block #" + to_string(index), last_block.current_block);
  return new_block;
}

int blockchain_size;
List *blocks = new List;
int Blockchain::build(int blockchain_size, bool show_blocks) {
  this->blockchain_size = blockchain_size;
  this->head_block->init(0, "HEAD", "NULL"); // being overwrited by list new block function
  this->blocks->append(this->head_block);

  this->head_block->print_block(true);
  cout << "\033[1;32mBlock #"<< this->head_block->block_index;
  cout << "\033[0;32m has been added to the blockchain.\033[0m\n";

  Block *current_block = this->head_block;
  for (int i = 0; i < blockchain_size - 1; i++) {

    Block *new_block = add_block(*current_block);
    this->blocks->append(new_block);
    if (show_blocks) {
      new_block->print_block(true);
    }
    cout << "\033[1;32mBlock #"<< new_block->block_index;
    cout << "\033[0;32m has been added to the blockchain.\033[0m\n";
    current_block = new_block;
  }
  cout << "\n\033[0;32mBlockchain with \033[1;32m" << this->blockchain_size << "\033[0;32m blocks built in ";
  printf("\033[1;32m%.2f seconds.\033[0m\n", (double)(clock() - this->tStart)/CLOCKS_PER_SEC);
  return 0;
}

int Blockchain::export_blockchain(string blockchain_name) {
  json blockchain;
  blockchain["blocks"] = { };
  for (int i = 0; i < this->blockchain_size; i++) {
    blockchain["blocks"][i] = { };
    Block *block = this->blocks->get_block(i, this->blocks);
    blockchain["blocks"][i]["block_index"] = block->block_index;
    blockchain["blocks"][i]["timestamp"] = block->timestamp;
    blockchain["blocks"][i]["data"] = block->data;
    blockchain["blocks"][i]["previous_block"] = block->previous_block;
    blockchain["blocks"][i]["this_block"] = block->current_block;
  }
  string filename = "blockchains/" + blockchain_name + ".json";
  ofstream o(filename);
  o << setw(4) << blockchain << endl;
  o.close();
  cout << "\033[0;32mCurrent blockchain exported to \033[1;32m" << filename << ".\033[0m" << endl;
  return 0;
}
int Blockchain::validate(Block block_1, Block block_2) {
  // 1. Check if indexs match up

  // 3. Check if  block1.hash == hash of block2.previous

  // 2. Hash block1 as HASH. check if HASH == block1.this_block. check if HASH == block2.previous
}
int Blockchain::import_blockchain(string blockchain_name, bool show_blocks) {
  string filename = "blockchains/" + blockchain_name + ".json";
  ifstream ifs(filename);
  json blockchain = json::parse(ifs);

  this->blockchain_size = blockchain["blocks"].size();
  this->head_block->init(0, "HEAD", "NULL"); // being overwrited by list new block function
  this->blocks->append(this->head_block);

  for (int i = 0; i < this->blockchain_size; i++) {
    Block *new_block = new Block;
    int _index = blockchain["blocks"][i]["block_index"];
    string _data = blockchain["blocks"][i]["data"];
    string _previous_block = blockchain["blocks"][i]["previous_block"];
    string _timestamp = blockchain["blocks"][i]["timestamp"];
    string _this_block = blockchain["blocks"][i]["this_block"];

    if (this->head_block == NULL) {
      this->head_block->init(_index, _data, _previous_block, true, _timestamp, _this_block);
      this->blocks->append(this->head_block);
    } else {
      new_block->init(_index, _data, _previous_block);
      this->blocks->append(new_block);
    }
    if (show_blocks) {
      new_block->print_block(true);
    }
    cout << "\033[1;32mBlock #"<< new_block->block_index;
    cout << "\033[0;32m has been added to the blockchain.\033[0m\n";
  }
  return 0;
}
