#include <string>
#include "main.h"
#include <fstream>
#include <iostream>
#include "json/json.hpp"
using json = nlohmann::json;
using namespace std;



Block *Blockchain::genesis_block() {
    Block *head_block = new Block;
    head_block->init(0, NULL, 9, "0");
    return head_block;
}

Block *Blockchain::new_block(int index, TransactionList *transactions, int proof_of_work, string previous_hash) {
    Block *new_block = new Block;
    new_block->init(index, transactions, proof_of_work, previous_hash);
    this->blocks->append(new_block);
}

int Blockchain::export_blockchain(string blockchain_name) {
    json blockchain;
    blockchain["blocks"] = { };
    for (int i = 0; i < this->blockchain_size + 1; i++) {
        blockchain["blocks"][i] = { };
        Block *block = this->blocks->get_block(i);
        blockchain["blocks"][i]["index"] = block->index;
        blockchain["blocks"][i]["timestamp"] = block->timestamp;
        blockchain["blocks"][i]["transactions"] = block->transactions->get_transactions();
        blockchain["blocks"][i]["previous_hash"] = block->previous_hash;
        blockchain["blocks"][i]["hash"] = block->this_hash;
    }
    string filename = blockchain_name + ".json";
    ofstream o(filename);
    o << setw(4) << blockchain << endl;
    o.close();
    cout << "\033[0;32mCurrent blockchain exported to \033[1;32m" << filename << ".\033[0m" << endl;
    return 0;
}