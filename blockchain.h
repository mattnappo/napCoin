#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <string>
using namespace std;

class Block {
private:
  string hash_block();
  string get_timestamp();
public:
  string current_block;
  int index;
  string timestamp;
	string data;
  string previous_block;
  int init(int index, string data, string previous_block);
  int print_block(bool spacing);
};

#endif
