#include "blockchain.h"
#include <iostream>

using namespace std;

int main() {
  Blockchain *blockchain = new Blockchain;
  blockchain->build(15, true);
  blockchain->export_blockchain("blockchain_0");
  // blockchain->import_blockchain("blockchain_0", true);
  cout << endl << "BLOCKS: " << endl;
  for (int i = 0; i < 10; i++) {
    blockchain->blocks->get_block(i, blockchain->blocks)->print_block(true);
  }

  /*
  cout << endl << "BLOCK 0: " << blockchain->blocks->get_block(0, blockchain->blocks)->previous_hash << endl;
  cout << endl << "BLOCK 1: " << blockchain->blocks->get_block(1, blockchain->blocks)->previous_hash << endl;
  cout << endl << "BLOCK 2: " << blockchain->blocks->get_block(2, blockchain->blocks)->previous_hash << endl;
  */
  return 0;
}
