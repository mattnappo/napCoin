#include "napcoin.h"
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

    TransactionList *tl = new TransactionList;

    tl->append(new_transaction("from", "to", 15));
    tl->append(new_transaction("from two", "to two", 94));
    tl->append(new_transaction("sdfiu", "sdfgjsdf", 34));


    Blockchain *b = new Blockchain;

    

    return 0;
}