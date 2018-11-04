#ifndef NODE_HPP
#define NODE_HPP

#include <string>
#include <vector>
#include "token.hpp"

struct Node
{
    std::string label;
    std::vector<struct Node*> children;
    std::vector<Token> tokens;
};

struct Node* get_node(std::string label);
void print_level_order(struct Node* root);

#endif // !NODE_HPP