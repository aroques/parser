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
        stats(token);

        if (token.instance == "stop")
        {
            token = get_next_token();
            return;
        }
        else print_error_and_exit(token_string(KEYWORD_TK, "stop"), token_string(token), token.line_number);
    }
    else print_error_and_exit(token_string(KEYWORD_TK, "start"), token_string(token), token.line_number);
}

void stats(Token& token) 
{
    stat(token);
    mStat(token);
    return;
}

void mStat(Token& token) 
{   
    std::set<std::string> stat_productions = {"scan", "block"};
    
    if (stat_productions.count(token.instance) > 0)
    {
        stat(token);
        mStat(token);
        return;
    }

    return;
}

void stat(Token& token) 
{
    if (token.instance == "scan")
    {
        in(token);
        return;
    }
    
    // if (token.instance == "out") out(token);
    
    if (token.instance == "block")
    {
        block(token);
        return;
    }  

    print_error_and_exit("scan or " + 
        token_string(KEYWORD_TK, "block"), token_string(token), token.line_number);
}

void in(Token& token) 
{
    if (token.instance == "scan")
    {
        token = get_next_token();

        if (token.type == IDENTIFIER_TK)
        {
            token = get_next_token();

            if (token.instance == ".")
            {
                token = get_next_token();
                return;
            }
            else print_error_and_exit(token_string(OPERATOR_DELIMITER_TK, "."), token_string(token), token.line_number);
        }
        else print_error_and_exit(token_string(IDENTIFIER_TK, ""), token_string(token), token.line_number);
    }
    else print_error_and_exit(token_string(KEYWORD_TK, "scan"), token_string(token), token.line_number);
}

// void out(Token& token) 
// {
//     if (token.instance == "[")
//     {
//         token = get_next_token();
        
//         // expr();

//         if (token.instance == "]")
//         {
//             token = get_next_token();
            
//             if (token.instance == ".")
//             {
//                 token = get_next_token();
//                 return;
//             }
//             else print_error_and_exit(token_string(OPERATOR_DELIMITER_TK, "."), token_string(token), token.line_number);
//         }
//         else print_error_and_exit(token_string(OPERATOR_DELIMITER_TK, "]"), token_string(token), token.line_number);
//     }
//     else print_error_and_exit(token_string(OPERATOR_DELIMITER_TK, "["), token_string(token), token.line_number);
// }
