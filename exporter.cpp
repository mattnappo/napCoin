#include "nlohmann/json.hpp"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
using json = nlohmann::json;

int main() {
  ifstream ifs("blockchains/blockchain_0.json");
  json blockchain = json::parse(ifs);
  cout << "size: " << blockchain["blocks"].size() << endl << endl;
  cout << blockchain["blocks"] << endl;
  cout << endl << endl << blockchain["blocks"][0] << endl;
}
