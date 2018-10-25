#include <iostream>
#include <fstream>

#include "parser.hpp"

// Prototypes
void validate_argc(int argc);
std::ifstream open_file(char* argv[]);

int main(int argc, char* argv[])
{
    validate_argc(argc);

    std::ifstream file;

    if (argc == 2) // Filename provided in argv[1]
    {
        file = open_file(argv);
        // Set cin to read from file
        std::cin.rdbuf(file.rdbuf());
    }

    parser();

    if (file.is_open()) file.close();

    return 0;
}

void validate_argc(int argc)
{
    if (argc > 2)
    {
        std::cout << "Too many arguments." << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

std::ifstream open_file(char* argv[])
{
    std::string filename = argv[1];
    filename += ".fs182";
    std::ifstream file(filename);

    if (!file.is_open())
    {
        std::cout << "Failed to open file." << std::endl;
        std::exit(EXIT_FAILURE);
    }

    return file;
}