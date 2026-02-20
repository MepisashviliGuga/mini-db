#include <iostream>
#include <string>
#include <sstream>
#include "Table.h"
#include "Row.h"

int main() {
    Table* table = new Table("db.bin");

    std::cout << "MiniDB Architecture Phase (3) Started." << std::endl;
    std::cout << "Type 'exit' to save and quit." << std::endl;

    while (true) {
        std::cout << "db > ";

        std::string input_line;
        if (!std::getline(std::cin, input_line)) {
            break;
        }
        std::stringstream ss(input_line);
        std::string keyword;
        ss >> keyword;
        for (char &c : keyword) {
            c = tolower(c);
        }

        if (keyword == "exit") {
            delete table; 
            break;
        } 
        
        else if (keyword == "insert") {
            Row row;
            if (!(ss >> row.id >> row.username >> row.email)) {
                std::cout << "Syntax error: insert <id> <name> <email>" << std::endl;
                continue;
            }
            table->row_insert(row);
            std::cout << "Executed." << std::endl;
        } 
        
        else if (keyword == "select") {
            table->select_all();
        } 
        
        else {
            if (!keyword.empty()) {
                std::cout << "Unrecognized command: " << keyword << std::endl;
            }
        }
    }

    return 0;
}