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

    cout << transaction_list->get_transactions();

    Blockchain *blockchain = new Blockchain;
    blockchain->blocks = transaction_list->get_transactions();
}