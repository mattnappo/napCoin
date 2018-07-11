// FOR BLOCKCHAIN
#include <iostream>
#include <string>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <time.h>
// FOR ARGON
#include "argon2/argon2.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define HASHLEN 32
#define SALTLEN 16

using namespace std;

class Block {
private:
  string convert_int(int n) {
    stringstream ss;
    ss << n;
    return ss.str();
  }
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
    if(ARGON2_OK != rc) {
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
  struct Node {
    Block *block;
    Node *next;
  };
  Node *head;
public:
  List() {
    head = NULL;
  }
  ~List() {
    while(head != NULL) {
      Node *n = head->next;
      delete head;
      head = n;
    }
  }
  void append(Block *block) {
    if(this->head == NULL) {
      this->head = new Node;
      this->head->block = block;
      this->head->next = NULL;
      return;
    }
    Node *current_node = this->head;
    while(current_node->next != NULL) {
      current_node = current_node->next;
    }
    Node *new_node = new Node;
    new_node->block = block;
    new_node->next = NULL;
    current_node->next = new_node;
  }
  void print_blocks() {
    Node *current_node = this->head;
    while(current_node != NULL) {
      current_node->block->print_block(false);
      current_node = current_node->next;
    }
  }
};

class Blockchain {
private:
  Block *head_block = new Block;
  List *blocks = new List;
  Block *add_block(Block last_block) {
    Block *new_block = new Block;
    int index = last_block.index + 1;
    new_block->init(index, "This is block #" + to_string(index), last_block.current_block);
    return new_block;
  }
public:
  int blockchain_size;
  int build(int blockchain_size, bool show_blocks) {
    this->blockchain_size = blockchain_size;
    this->head_block->init(0, "HEAD", "NULL"); // being overwrited by list new block function
    this->blocks->append(this->head_block);

    Block *current_block = this->head_block;
    for (int i = 0; i < blockchain_size; i++) {
      Block *new_block = add_block(*current_block);
      this->blocks->append(new_block);
      if (show_blocks == true) {
        new_block->print_block(true);
      }
      current_block = new_block;
      cout << "\033[1;32mBlock #"<< current_block->index;
      cout << "\033[0;32m has been added to the blockchain.\033[0m\n";
      current_block = new_block;
    }
    return 0;
  }
  int export_blockchain() {

    // Block *current_block = this->head_block;
    // for (int i = 0; i < blockchain_size; i++) {
    //   Block *new_block = add_block(*current_block);
    //   this->blocks->append(new_block);
    //   if (show_blocks) {
    //     new_block->print_block();
    //     current_block = new_block;
    //   }
    //   current_block = new_block;
    // }


    ofstream file;
    file.open("blockchains/test.txt");
    file << "Writing this to a file.\n";
    file.close();
    cout << "done" << endl;
    return 0;
  }

};

int main() {
  clock_t tStart = clock();
  Blockchain *blockchain = new Blockchain;
  blockchain->build(20, false);
  // blockchain->export_blockchain();

  cout << "\033[0;32mBlockchain with \033[1;32m" << blockchain->blockchain_size << "\033[0;32m blocks built in ";
  printf("\033[1;32m%.2f seconds.\033[0m\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
  return 0;
}