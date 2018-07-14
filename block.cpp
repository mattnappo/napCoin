#include "blockchain.h"
#include "json/json.hpp"
#include "argon2/argon2.h"
#include <iostream>
using namespace std;
// THERE IS SOME SORT OF PROBLEM WITH WHERE THE HASHES GO

#define HASHLEN 32
#define SALTLEN 16

string Block::hash_block() {
  string TO_HASH = to_string(this->block_index) + this->timestamp + this->data + this->previous_block /* + this->current_block */;
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
  return hash;
}
string Block::get_timestamp() {
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
string current_block;
int block_index;
string timestamp;
string data;
string previous_block;
int Block::init(int index, string data, string previous_block,
  bool from_import, string timestamp, string current_block) {
  if (from_import) {
    this->timestamp = timestamp;
    this->current_block = current_block;
  } else {
    this->timestamp = get_timestamp();
    this->current_block = hash_block();
  }
  this->block_index = index;
  this->data = data;
  this->previous_block = previous_block;
  return 0;
}
int Block::print_block(bool spacing) {
  if (spacing) { cout << endl; }
  cout << "Previous block: " << this->previous_block << endl;
  cout << "Index:          " << this->block_index << endl;
  cout << "Timestamp:      " << this->timestamp << endl;
  cout << "Data:           " << this->data << endl;
  cout << "This block:     " << this->current_block << endl;
  if (spacing) { cout << endl; }
  return 0;
}
