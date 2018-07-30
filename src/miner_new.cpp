#include <sstream>
#include <string>
#include <vector>

#include "crow.h"

int main() {
    crow:::SimpleApp node;

    CROW_ROUTE(node, "/transaction").methods("POST"_method)
    ([](const crow::request &req){
        auto x -
    });
}