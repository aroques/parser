#include <iostream>
#include <vector>
#include <algorithm>

#include "string/include/string.hpp"

#include "scanner/include/token.hpp"

#include "parser/include/Node.hpp"

static int height(struct Node* node) 
{
    if (node == NULL)
        // null leaf, so return 0
        return 0;
    
    else if (node->children.size() == 0)
        // A leaf with no children,
        // so return 1 becuase it does count towards the height of the tree
        return 1;
    
    else
    {
        // Compute the height of each subtree
        std::vector<int> heights;
        
        for (auto child: node->children) 
            heights.push_back(height(child) + 1);
    
        // Use the largest one
        return *max_element(heights.begin(), heights.end());
    }
}

static void print_given_level(struct Node* root, int level) 
{ 
    if (root == NULL) 
        return; 
    
    if (level == 1)
        std::cout << root->label << " "; 
    
    else if (level > 1) 
    {
        for (auto child: root->children) 
        {
            print_given_level(child, level - 1); 
        }
    } 
}

/*
    Code for level order traversal adapted from:
      https://www.geeksforgeeks.org/level-order-tree-traversal/
*/
void print_level_order(struct Node* root) 
{
    int h = height(root); 
    
    std::cout << "height: " << std::to_string(h) << "\n\n";

    for (int i = 1; i <= h; i++)
    {
        print_given_level(root, i);
        std::cout << std::endl;
    }
}

static void print_node(struct Node* node, int level) 
{
    for (int i = 0; i < level; i++)
        std::cout << "--";

    std::cout << " " << node->label << ": ";

    std::vector<std::string> tokens;

    for (auto token: node->tokens)
        tokens.push_back(token_string(token));
    
    std::cout << join(tokens, ", ") << std::endl;
}

void print_preorder(struct Node* node, int level = 0) 
{
    if (node == NULL) 
        return; 
    
    print_node(node, level);

    if (node->children.size() == 0)
        return;
    
    for (auto child: node->children) 
        print_preorder(child, level + 1);
}
