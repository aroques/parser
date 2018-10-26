#include "token.hpp"

#include <set>
#include <iostream>

static char format_str[100] = "%-20s %-15s %-2s\n";

static std::string get_token_type(int type);

void print_token_header()
{
    printf(format_str, "Type", "Instance", "Line No");
    for (int i = 0; i < 44; i++) printf("-");
    printf("\n");
}

void print_token(Token t)
{
    printf(format_str, get_token_type(t.type).c_str(),
        t.instance.c_str(), std::to_string(t.line_number).c_str());
}

int get_token_type(int final_state, std::string token_instance)
{
    std::set<std::string> keywords = { "start", "stop", "loop", "void", 
        "var", "return", "scan", "out", "program", "if", "then", "let",
        "integer"
    };

    if (keywords.count(token_instance) > 0) 
    {
        return KEYWORD_TK;
    }
    else
    {
        return final_state;
    }
}

static std::string get_token_type(int type)
{
    switch (type)
    {
        case OPERATOR_DELIMITER_TK: 
            return "operator/delimiter";

        case IDENTIFIER_TK:
            return "identifier";

        case KEYWORD_TK:
            return "keyword";

        case NUMBER_TK:
            return "number";

        case END_OF_FILE_TK:
            return "EOF";
        
        default:
            return "token type not defined";
    }
}

std::string token_string(Token t)
{
    return token_string(t.type, t.instance);
}

std::string token_string(int token_type, std::string token_instance)
{
    switch (token_type)
    {
        case OPERATOR_DELIMITER_TK: 
            return token_instance + " token";

        case IDENTIFIER_TK:
            return "identifier token";

        case KEYWORD_TK:
            return token_instance + " keyword";

        case NUMBER_TK:
            return "number token";

        case END_OF_FILE_TK:
            return "EOF token";
        
        default:
            return "token type not defined";
    }
}