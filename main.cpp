#include "blockchain.h"

int main() {
  Blockchain *blockchain = new Blockchain;
  // blockchain->build(5, true);
  // blockchain->blocks->get_block(4, blockchain->blocks)->print_block(true);
  // blockchain->export_blockchain("blockchain_0");
  blockchain->import_blockchain("blockchain_0", true);

  return 0;
}
