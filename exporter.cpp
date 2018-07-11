#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>
using namespace rapidjson;
using namespace std;

string importer() {
  ifstream t("blockchains/blockchain_2.json");
  string RAW((istreambuf_iterator<char>(t)), istreambuf_iterator<char>());
  return RAW;
}
int main() {
  const char *json = importer().c_str();
  // const char* json = "{\"project\":\"rapidjson\",\"stars\":10}";
  cout << importer() << endl;

  Document document;
  document.Parse(json);


  assert(document.IsObject());

  assert(document.HasMember("hello"));
assert(document["hello"].IsString());
printf("hello = %s\n", document["hello"].GetString());
}
