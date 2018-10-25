#include <iostream>

#include "productions.hpp"
#include "scanner/include/scanner.hpp"
#include "scanner/include/token.hpp"


void parser()
{
    std::cout << "parsing..." << std::endl;

    Token token;
    
    S(token);

    if (token.type != END_OF_FILE_TK) 
    {
        std::cout << "parser error: start production did not return EOF token." << std::endl;
        std::exit(EXIT_FAILURE);
    }

    std::cout << "successful parse." << std::endl;

    return;

}

