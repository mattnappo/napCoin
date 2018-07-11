#include "nlohmann/json.hpp"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
using json = nlohmann::json;

int main() {
  ifstream ifs("blockchains/blockchain_0.json");
  json blockchain = json::parse(ifs);
  cout << "fial: " << blockchain << endl << endl;
  cout << blockchain << endl;
  cout << endl << endl << endl;
  cout << blockchain["blocks"];
}
