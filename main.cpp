#include "blockchain.h"

using namespace std;

int main() {
  Blockchain *blockchain = new Blockchain;
  // blockchain->build(5, false);
  // blockchain->export_blockchain("blockchain_0");
  blockchain->import_blockchain("blockchain_0", true);
  return 0;
}
