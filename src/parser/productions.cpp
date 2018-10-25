#include <iostream>

#include "scanner/include/scanner.hpp"

void S(Token& token) 
{
    token = Token {
        END_OF_FILE_TK,
        "",
        1
    };

    return;

    // if (token.type == b) 
    // { 
    //     token = get_next_token(); 
    //     A();  
    //     return; 
    // } 
    
    // if (token.type == c) 
    // { 
    //     token = get_next_token();  
    //     return; 
    // } 

    std::cout << "parser error: expecting t." << std::endl;
    std::exit(EXIT_FAILURE);
}
