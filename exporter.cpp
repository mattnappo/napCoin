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
  ifstream t("blockchains/blockchain_0.json");
  string RAW((istreambuf_iterator<char>(t)), istreambuf_iterator<char>());
  return RAW;
}
int main() {
  const string RAW_JSON = importer();
  cout << RAW_JSON << endl;
  const char *json = RAW_JSON.c_str();
  // const char *json = "{\"project\":\"rapidjson\",\"stars\":10}";
  Document document;
  document.Parse(json);

  Value &blocks = document["blocks"];
  for (SizeType i = 0; i < blocks.Size(); i++){
    CCLOG("{x=%f, y=%f}", blocks[i]["x"].GetDouble(), blocks[i]["y"].GetDouble());
  }

  StringBuffer block_buffer;
  Writer<StringBuffer> block_writer(block_buffer);
  blocks.Accept(block_writer);
  cout << "Block0: " << block_buffer.GetString() << endl;

/*
  StringBuffer buffer;
  Writer<StringBuffer> writer(buffer);
  document.Accept(writer);
  cout << buffer.GetString() << endl;
  return 0;
*/
}
