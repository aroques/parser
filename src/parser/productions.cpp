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
        
                if (token.type == NUMBER_TK)
                {
                    token = get_next_token(); 
                    vars(token);
                    return;
                } 
                else print_error_and_exit(token_string(NUMBER_TK, ""), token_string(token), token.line_number);
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
    std::set<std::string> stat_productions = 
        {"scan", "out", "block", "if", "loop", "let"};
    
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
    
    if (token.instance == "out") 
    {
        out(token);
        return;
    }
    
    if (token.instance == "block")
    {
        block(token);
        return;
    }  
    
    if (token.instance == "if")
    {
        if_(token);
        return;
    }  
    
    if (token.instance == "loop")
    {
        loop(token);
        return;
    }  
    
    if (token.instance == "let")
    {
        assign(token);
        return;
    }  

    print_error_and_exit("scan, out, block, if, loop, or " + 
        token_string(KEYWORD_TK, "let"), token_string(token), token.line_number);
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

void out(Token& token) 
{
    if (token.instance == "out")
    {
        token = get_next_token();
        
        if (token.instance == "[")
        {
            token = get_next_token();
            
            expr(token);

            if (token.instance == "]")
            {
                token = get_next_token();
                
                if (token.instance == ".")
                {
                    token = get_next_token();
                    return;
                }
                else print_error_and_exit(token_string(OPERATOR_DELIMITER_TK, "."), token_string(token), token.line_number);
            }
            else print_error_and_exit(token_string(OPERATOR_DELIMITER_TK, "]"), token_string(token), token.line_number);
        }
        else print_error_and_exit(token_string(OPERATOR_DELIMITER_TK, "["), token_string(token), token.line_number);
    }
    else print_error_and_exit(token_string(KEYWORD_TK, "out"), token_string(token), token.line_number);
}

void expr(Token& token) 
{   
    A(token);
    
    if (token.instance == "/" || token.instance == "*")
    {
        token = get_next_token();
        expr(token);
        return;
    }

    return;
}

void A(Token& token) 
{   
    M(token);
    
    if (token.instance == "+" || token.instance == "-")
    {
        token = get_next_token();
        A(token);
        return;
    }

    return;
}

void M(Token& token) 
{   
    if (token.instance == "-")
    {
        token = get_next_token();
        M(token);
        return;
    }

    R(token);
    return;
}

void R(Token& token) 
{   
    if (token.instance == "(")
    {
        token = get_next_token();
        expr(token);

        if (token.instance == ")")
        {
            token = get_next_token();
            return;
        }
        else print_error_and_exit(token_string(OPERATOR_DELIMITER_TK, ")"), token_string(token), token.line_number);
    }
    
    if (token.type == IDENTIFIER_TK || token.type == NUMBER_TK)
    {
        token = get_next_token();
        return;
    }
    
    print_error_and_exit(token_string(IDENTIFIER_TK, "") + ", " + token_string(NUMBER_TK, "") + ", or "
        + token_string(OPERATOR_DELIMITER_TK, "("), token_string(token), token.line_number);
}

void if_(Token& token) 
{   
    if (token.instance == "if")
    {
        token = get_next_token();
        conditionalStat(token);
        return;
    }
    else print_error_and_exit(token_string(KEYWORD_TK, "if"), token_string(token), token.line_number);
}

void loop(Token& token) 
{   
    if (token.instance == "loop")
    {
        token = get_next_token();
        conditionalStat(token);
        return;
    }
    else print_error_and_exit(token_string(KEYWORD_TK, "loop"), token_string(token), token.line_number);
}

void conditionalStat(Token& token)
{
    if (token.instance == "(")
    {
        token = get_next_token();
        
        expr(token);
        RO(token);
        expr(token);

        if (token.instance == ")")
        {
            token = get_next_token();
            stat(token);
            return;
        }
        else print_error_and_exit(token_string(OPERATOR_DELIMITER_TK, ")"), token_string(token), token.line_number);
    }
    else print_error_and_exit(token_string(OPERATOR_DELIMITER_TK, "("), token_string(token), token.line_number);
}

void RO(Token& token) 
{   
    if (token.instance == "<" || token.instance == ">" || token.instance == "=")
    {
        token = get_next_token();
        
        if (token.instance == "=")
        {
            token = get_next_token();
            return;
        }

        return;
    }

    print_error_and_exit("<, >, or " + 
        token_string(OPERATOR_DELIMITER_TK, "="), token_string(token), token.line_number);
}

void assign(Token& token) 
{   
    if (token.instance == "let")
    {
        token = get_next_token();
        
        if (token.type == IDENTIFIER_TK)
        {
            token = get_next_token();

            if (token.instance == "=")
            {
                token = get_next_token();
                expr(token);
                
                if (token.instance == ".")
                {
                    token = get_next_token();
                    return;
                }
                else print_error_and_exit(token_string(OPERATOR_DELIMITER_TK, "."), token_string(token), token.line_number);
            }
            else print_error_and_exit(token_string(OPERATOR_DELIMITER_TK, "="), token_string(token), token.line_number);
        }
        else print_error_and_exit(token_string(IDENTIFIER_TK, ""), token_string(token), token.line_number);
    }
    else print_error_and_exit(token_string(KEYWORD_TK, "let"), token_string(token), token.line_number);
}