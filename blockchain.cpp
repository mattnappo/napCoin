// FOR BLOCKCHAIN
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

#define HASHLEN 32
#define SALTLEN 16

class Block {
private:
  string hash_block() {
    string TO_HASH = to_string(this->index) + this->timestamp + this->data + this->previous_block + this->current_block;
    uint8_t hash1[HASHLEN];
    uint8_t hash2[HASHLEN];
    uint8_t salt[SALTLEN];
    memset( salt, 0x00, SALTLEN );
    uint8_t *pwd = (uint8_t *)strdup(TO_HASH.c_str());
    uint32_t pwdlen = strlen((char *)pwd);
    uint32_t t_cost = 2;            // 1-pass computation
    uint32_t m_cost = (1<<16);      // 64 mebibytes memory usage
    uint32_t parallelism = 1;       // number of threads and lanes
    argon2i_hash_raw(t_cost, m_cost, parallelism, pwd, pwdlen, salt, SALTLEN, hash1, HASHLEN);
    argon2_context context = {
      hash2,  /* output array, at least HASHLEN in size */
      HASHLEN, /* digest length */
      pwd, /* password array */
      pwdlen, /* password length */
      salt,  /* salt array */
      SALTLEN, /* salt length */
      NULL, 0, /* optional secret data */
      NULL, 0, /* optional associated data */
      t_cost, m_cost, parallelism, parallelism,
      ARGON2_VERSION_13, /* algorithm version */
      NULL, NULL, /* custom memory allocation / deallocation functions */
      /* by default only internal memory is cleared (pwd is not wiped) */
      ARGON2_DEFAULT_FLAGS
    };
    int rc = argon2i_ctx( &context );
    if (ARGON2_OK != rc) {
      printf("Error: %s\n", argon2_error_message(rc));
      exit(1);
    }
    free(pwd);
    stringstream hexstr;
    for (int i = 0; i < HASHLEN; ++i) {
      int a = static_cast< int >(hash2[i]);
      hexstr << setfill('0') << setw(2) << hex << a;
    }
    string hash = hexstr.str();
    /*
    if (memcmp(hash1, hash2, HASHLEN)) {
      printf("fail\n");
      for ( int i=0; i<HASHLEN; ++i ) {
        printf( "%02x", hash2[i] );
      }
      printf("\nfail\n");
    }
    else printf("ok\n");
    */
    return hash;
  }
  string get_timestamp() {
    time_t t = time(0);   // get time now
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
public:
  string current_block; // hash of this block
  int index;
  string timestamp;
	string data;
  string previous_block; // hash of the previous block
int init(int index, string data, string previous_block) {
  this->timestamp = get_timestamp();
  this->index = index;
  this->data = data;
  this->previous_block = previous_block;
  this->current_block = hash_block();
  return 0;
}
int print_block(bool spacing) {
  if (spacing) { cout << endl; }
  cout << "This block: " << this->current_block << endl;
  cout << "Index: " << this->index << endl;
  cout << "Timestamp: " << this->timestamp << endl;
  cout << "Data: " << this->data << endl;
  cout << "Previous block: " << this->previous_block << endl;
  if (spacing) { cout << endl; }
  return 0;
}
};
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
  void print_blocks() {
    Node *current_node = this->head;
    while (current_node != NULL) {
      current_node->block->print_block(false);
      current_node = current_node->next;
    }
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
    this->blocks->head->block = this->head_block;

    cout << "block:" << endl << endl;
    this->head_block->print_block(true);
    cout << endl << "end block" << endl;

    Block *current_block = this->head_block;
    for (int i = 0; i < blockchain_size; i++) {
      Block *new_block = add_block(*current_block);
      this->blocks->append(new_block);
      if (show_blocks == true) {
        new_block->print_block(true);
      }
      cout << "\033[1;32mBlock #"<< current_block->index;
      cout << "\033[0;32m has been added to the blockchain.\033[0m\n";
      current_block = new_block;
    }
    return 0;
  }

  int export_blockchain(string blockchain_name, bool print_chain) {
    json blockchain;
    blockchain["blocks"] = { };
    // blockchain["blocks"][0] = { };
    // cout << blockchain["blocks"][0] << endl;
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
      if (show_blocks == true) {
        new_block->print_block(true);
      }
      cout << "\033[1;32mBlock #"<< new_block->index;
      cout << "\033[0;32m has been added to the blockchain.\033[0m\n";
    }
    return 0;
  }

};

int main() {
  clock_t tStart = clock();
  Blockchain *blockchain = new Blockchain;
  blockchain->build(3, true);
  //blockchain->export_blockchain("blockchain_10", true);
  // blockchain->import_blockchain("blockchain_10", true);


  cout << "\033[0;32mBlockchain with \033[1;32m" << blockchain->blockchain_size << "\033[0;32m blocks built in ";
  printf("\033[1;32m%.2f seconds.\033[0m\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
  return 0;
}
