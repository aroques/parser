#include <iostream>

#include "scanner/include/scanner.hpp"
#include "scanner/include/token.hpp"

#include "parser/include/productions.hpp"
#include "parser/include/error_handling.hpp"

void program(Token& token) 
{
    if (token.instance == "void") 
    { 
        token = get_next_token(); 
        vars(token);
        block(token);
        return; 
    }
    else print_error_and_exit(token_string(KEYWORD_TK, "void"), token_string(token), token.line_number);
}

void vars(Token& token) 
{
    if (token.instance == "var") 
    {
        token = get_next_token(); 
        
        if (token.type == IDENTIFIER_TK)
        {
            token = get_next_token(); 
        
            if (token.instance == ":")
            {
                token = get_next_token(); 
        
                if (token.instance == "integer")
                {
                    token = get_next_token(); 
                    vars(token);
                    return;
                } 
                else print_error_and_exit(token_string(KEYWORD_TK, "integer"), token_string(token), token.line_number);
            }
            else print_error_and_exit(token_string(OPERATOR_DELIMITER_TK, ":"), token_string(token), token.line_number);
        }
        else print_error_and_exit(token_string(IDENTIFIER_TK, ""), token_string(token), token.line_number);
    }

    return;
}

void block(Token& token) 
{
    if (token.instance == "start") 
    { 
        token = get_next_token(); 
        
        vars(token);

        if (token.instance == "stop")
        {
            token = get_next_token();
            return;
        }
        else print_error_and_exit(token_string(KEYWORD_TK, "stop"), token_string(token), token.line_number);
    }
    else print_error_and_exit(token_string(KEYWORD_TK, "start"), token_string(token), token.line_number);

    return;
}
