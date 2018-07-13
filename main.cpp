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


int main() {
  Blockchain *blockchain = new Blockchain;
  blockchain->build(5, true);
  blockchain->export_blockchain("blockchain_0");
  // blockchain->import_blockchain("blockchain_0", true);
  return 0;
}
