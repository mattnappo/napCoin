#include "linker.h"
#include "json/json.hpp"
#include <iostream>

using json = nlohmann::json;

int main() {
    json x;
    x["from"] = "FROM_TEST";
    x["to"] = "TO_TEST";
    x["amount"] = 10;
    TransactionList *transaction_list = new TransactionList;
    transaction_list->append(x);

    std::cout << transaction_list->get_transaction(0, transaction_list) << std::endl;
}