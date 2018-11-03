#include "node.hpp"

struct node* get_node(std::string label)
{
    struct node* temp =  new struct node();
    temp->label = label;
    return temp;
}
