#include "main.h"
#include "json/json.hpp"
#include <iostream>
#include <string>
using namespace std;
using json = nlohmann::json;
json new_transaction(string from, string to, int amount) {
    json x;
    x["from"] = from;
    x["to"] = to;
    x["amount"] = amount;
    return x;
}
int main() {
    json one = new_transaction("from", "to", 15);
    json two = new_transaction("from two", "to two", 94);
    json three = new_transaction("sdfiu", "sdfgjsdf", 34);
    
    TransactionList *transaction_list = new TransactionList;
    
    transaction_list->append(one);
    transaction_list->append(two);
    transaction_list->append(three);

    cout << transaction_list->get_transaction(0) << endl;
    cout << transaction_list->get_transaction(1) << endl;
    cout << transaction_list->get_transaction(2) << endl;

    cout << endl << endl << endl << endl;

    cout << transaction_list->get_transactions() << endl;

    Blockchain *blockchain = new Blockchain;
    int _index = 0;
    TransactionList *_transaction_list = transaction_list;
    int _proof_of_work = 100;
    string _previous_hash = "blockchain->blocks->get_block(0)->this_hash";
    // string _previous_hash = blockchain->blocks->get_block(0)->this_hash;
    
    // blockchain->create_genesis_block();
    // blockchain->add_block(_index, _transaction_list, _proof_of_work, _previous_hash);

    // blockchain->export_blockchain("HEAD.json");
}