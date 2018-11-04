#include <iostream>

#include "scanner/include/scanner.hpp"
#include "scanner/include/token.hpp"

#include "parser/include/Node.hpp"
#include "parser/include/productions.hpp"
#include "parser/include/error_handling.hpp"

Node* parser()
{
    std::cout << "parsing..." << std::endl;

    Token token = get_next_token();
    
    Node* root; 

    root = program(token);

    if (token.type != END_OF_FILE_TK) 
    {
        print_error_and_exit(token_string(END_OF_FILE_TK, ""), token_string(token), token.line_number);
    }

    std::cout << "successful parse." << std::endl;

    print_level_order(root);

    return root;

}

