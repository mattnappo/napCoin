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
  ifstream t("blockchains/blockchain_1.json");
  string RAW((istreambuf_iterator<char>(t)), istreambuf_iterator<char>());
  return RAW;
}
int main() {
  const string RAW_JSON = importer();
  cout << RAW_JSON << endl;
  // 1. Parse a JSON string into DOM.
  const char* json = RAW_JSON.c_str();
  Document d;
  d.Parse(json);

  // 2. Modify it by DOM.
  Value& s = d["stars"];
  s.SetInt(s.GetInt() + 1);

  // 3. Stringify the DOM
  StringBuffer buffer;
  Writer<StringBuffer> writer(buffer);
  d.Accept(writer);

  // Output {"project":"rapidjson","stars":11}
  std::cout << buffer.GetString() << std::endl;
  return 0;
}
