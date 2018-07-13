// FOR BLOCKCHAIN
#include "blockchain.h"
#include <iostream>
#include <string>
#include <ctime>
#include <sstream>
#include <time.h>
#include <fstream>
#include "json/json.hpp"
// FOR ARGON
#include "argon2/argon2.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
using namespace std;
using json = nlohmann::json;

class List {
private:
  struct Node {
    Block *block;
    Node *next;
  };
public:
  Node *head;
  List() {
    head = NULL;
  }
  ~List() {
    while (head != NULL) {
      Node *n = head->next;
      delete head;
      head = n;
    }
  }
  void append(Block *block) {
    if (this->head == NULL) {
      this->head = new Node;
      this->head->block = block;
      this->head->next = NULL;
      return;
    }
    Node *current_node = this->head;
    while (current_node->next != NULL) {
      current_node = current_node->next;
    }
    Node *new_node = new Node;
    new_node->block = block;
    new_node->next = NULL;
    current_node->next = new_node;
  }
  Block *get_block(int index, List *list) {
    Node *temp_node = list->head;
    int counter = 0;
    while (temp_node != NULL) {
      if (index == counter) {
        break;
      }
      temp_node = temp_node->next;
      counter++;
    }
    return temp_node->block;
  }
};

class Blockchain {
private:
  clock_t tStart = clock();
  Block *head_block = new Block;
  Block *add_block(Block last_block) {
    Block *new_block = new Block;
    int index = last_block.index + 1;
    new_block->init(index, "This is block #" + to_string(index), last_block.current_block);
    return new_block;
  }
public:
  int blockchain_size;
  List *blocks = new List;
  int build(int blockchain_size, bool show_blocks) {
    this->blockchain_size = blockchain_size;
    this->head_block->init(0, "HEAD", "NULL"); // being overwrited by list new block function
    this->blocks->append(this->head_block);

    this->head_block->print_block(true);
    Block *current_block = this->head_block;
    for (int i = 0; i < blockchain_size; i++) {

      Block *new_block = add_block(*current_block);
      this->blocks->append(new_block);
      if (show_blocks) {
        new_block->print_block(true);
      }
      cout << "\033[1;32mBlock #"<< current_block->index;
      cout << "\033[0;32m has been added to the blockchain.\033[0m\n";
      current_block = new_block;
    }
    cout << "\n\033[0;32mBlockchain with \033[1;32m" << this->blockchain_size << "\033[0;32m blocks built in ";
    printf("\033[1;32m%.2f seconds.\033[0m\n", (double)(clock() - this->tStart)/CLOCKS_PER_SEC);
    return 0;
  }

  int export_blockchain(string blockchain_name) {
    json blockchain;
    blockchain["blocks"] = { };
    for (int i = 0; i < this->blockchain_size; i++) {
      blockchain["blocks"][i] = { };
      Block *block = this->blocks->get_block(i, this->blocks);
      blockchain["blocks"][i]["index"] = block->index;
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

  int import_blockchain(string blockchain_name, bool show_blocks) {
    string filename = "blockchains/" + blockchain_name + ".json";
    ifstream ifs(filename);
    json blockchain = json::parse(ifs);

    this->blockchain_size = blockchain["blocks"].size();
    this->head_block->init(0, "HEAD", "NULL"); // being overwrited by list new block function
    this->blocks->append(this->head_block);

    for (int i = 0; i < this->blockchain_size; i++) {
      Block *new_block = new Block;
      int _index = blockchain["blocks"][i]["index"];
      string _data = blockchain["blocks"][i]["data"];
      string _previous_block = blockchain["blocks"][i]["previous_block"];

      if (this->head_block == NULL) {
        this->head_block->init(_index, _data, _previous_block);
        this->blocks->append(this->head_block);
      } else {
        new_block->init(_index, _data, _previous_block);
        this->blocks->append(new_block);
      }
      if (show_blocks) {
        new_block->print_block(true);
      }
      cout << "\033[1;32mBlock #"<< new_block->index;
      cout << "\033[0;32m has been added to the blockchain.\033[0m\n";
    }
    return 0;
  }

};

int main() {
  Blockchain *blockchain = new Blockchain;
  blockchain->build(5, true);
  blockchain->export_blockchain("blockchain_0");
  // blockchain->import_blockchain("blockchain_0", true);
  return 0;
}
