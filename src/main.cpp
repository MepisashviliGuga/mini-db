#include <iostream>
#include <string>

int main()
{
    while (true)
    {
        std::string command;
        std::cout << "db > ";
        if (!std::getline(std::cin, command))
        {
            break;
        };
        if (command == "exit")
            break;
        else
        {
            std::cout << "Unrecognized command\n";
        }
    }
    return 0;
}