#include <sstream>
#include <string>
#include <vector>

#include "napcoin.h"
#include "crow_all.h"

// curl "localhost:8080/transaction" -H "Content-Type: application/json" -d '{"from": "akjflw", "to":"fjlakdj", "amount": 3}'

int main() {
    TransactionList *transactions = new TransactionList;
    crow::SimpleApp node;
    CROW_ROUTE(node, "/transaction").methods("POST"_method)
    ([](const crow::request &req) {
        auto new_transaction = crow::json::load(req.body);
        std::string header_str = req.get_header_value("Content-Type");
        if (!new_transaction)
            return crow::response(400);
        std::cout << "New Transaction" << std::endl;
        std::cout << "FROM:   " << new_transaction["from"] << std::endl;
        std::cout << "TO:     " << new_transaction["to"] << std::endl;
        std::cout << "AMOUNT: " << new_transaction["amount"] << std::endl;
        // transactions->append(new_transaction);
        crow::response response = (crow::response)"Transaction completed successfully.\n";
        return response;
    });

    node.port(8080)
        .multithreaded()
        .run();
}