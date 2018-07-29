#include "blockchain.h"

using namespace std;

int main() {
  Blockchain *blockchain = new Blockchain;
  blockchain->build(100, true);
  blockchain->export_blockchain("HEAD");

  Blockchain *miner = new Blockchain;
  miner->import_blockchain("HEAD", true);
  // blockchain->import_blockchain("blockchain_0", true);
  return 0;
}
