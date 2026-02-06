#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <db.h>
#include <cstring>
#include <fstream>

int main()
{
    std::vector<Row> inmemorydatabase;
    std::ifstream source_file("db.bin",std::ios::binary);

    if(source_file){

        Row temp_row;
        while (source_file.read(reinterpret_cast<char*>(&temp_row), sizeof(Row))) {
                 inmemorydatabase.push_back(temp_row);
        }
        source_file.close();
    }

    while (true)
    {
        std::string input_line;
        std::cout << "db > ";
        if (!std::getline(std::cin, input_line))
        {
            break;
        };
        if (input_line == "exit")
            break;
        std::stringstream ss(input_line);
        std::string keyword;
        ss >> keyword;
        Row entry;
        for (char &c : keyword)
        {
            c = tolower(c);
        }
        if (keyword == "insert")
        {
            int id;
            std::string username;
            std::string email;

            if (ss >> id >> username >> email)
            {
                entry.id = id;
                if (username.size() >= 32 || email.size() >= 256)
                {
                    std::cout << "It is Big Username or Email\n";
                    continue;
                }

                for (int i = 0; i < username.size(); i++)
                {
                    entry.username[i] = username[i];
                }
                for (int i = 0; i < email.size(); i++)
                {
                    entry.email[i] = email[i];
                }
                entry.username[username.size()] = '\0';
                entry.email[email.size()] = '\0';
                inmemorydatabase.push_back(entry);

                std::ofstream db_file("db.bin",std::ios::app | std::ios::binary);
                if(!db_file){
                    std::cout<<"INTERNAL ERROR, could not open file for saving";
                    return 1;
                }
                db_file.write(reinterpret_cast<char*>(&entry),sizeof(Row));
                db_file.close();
            

            }
            else
            {
                std::cout << "Syntax Error\n";
                continue;
            }
        }
        else if (keyword == "select")
        {
            for (const Row& row : inmemorydatabase)
            {
                std::cout << "id = " << row.id << ", username = " << row.username << ", email = " << row.email << '\n';
            }            
        }
    }
    return 0;
}