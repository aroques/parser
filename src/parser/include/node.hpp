#ifndef NODE_HPP
#define NODE_HPP

#include <string>
#include <vector>
#include "token.hpp"

struct node
{
    std::string label;
    std::vector<struct node*> children;
    std::vector<Token> tokens;
};

struct node* get_node(std::string label);

#endif // !NODE_HPP