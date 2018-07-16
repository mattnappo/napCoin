#include "blockchain.h"
#include <iostream>

using namespace std;

int main() {
  Blockchain *blockchain = new Blockchain;
  blockchain->build(5, true);
  blockchain->export_blockchain("blockchain_0");
  // blockchain->import_blockchain("blockchain_0", true);

  cout << endl << "BLOCK 0: " << blockchain->blocks->get_block(0, blockchain->blocks)->previous_block << endl;
  cout << endl << "BLOCK 1: " << blockchain->blocks->get_block(1, blockchain->blocks)->previous_block << endl;
  cout << endl << "BLOCK 2: " << blockchain->blocks->get_block(2, blockchain->blocks)->previous_block << endl;

  return 0;
}
