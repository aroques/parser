#include "parser/include/Node.hpp"

#include <iostream>
#include <vector>
#include <algorithm>

struct Node* get_node(std::string label)
{
    struct Node* temp =  new struct Node();
    temp->label = label;
    return temp;
}

static int height(struct Node* node) 
{ 
    if (node == NULL) 
        return 0; 
    else
    { 
        // Compute the height of each subtree
        std::vector<int> heights;
        for (auto child: node->children) 
        {
            if (child == NULL) 
                break;
            int h = height(child);
            heights.push_back(h);
        }
    
        // Use the largest one
        return *max_element(heights.begin(), heights.end()) + 1;
    } 
}

static void print_given_level(struct Node* root, int level) 
{ 
    if (root == NULL) 
        return; 
    
    if (level == 1)
        std::cout << root->label << ", "; 
    
    else if (level > 1) 
    {
        for (auto child: root->children) 
        {
            if (child == NULL) 
                break;
            print_given_level(child, level - 1); 
        }
    } 
}

void print_level_order(struct Node* root) 
{ 
    int h = height(root); 

    for (int i = 1; i <= h; i++)
    {
        print_given_level(root, i);
        std::cout << std::endl;
    }
}



