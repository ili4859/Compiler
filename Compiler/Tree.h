#pragma once
#include "Node.h"
#include "variable.h"
#include "variable_table.h"

class Tree {
private:
    variable_table _all_variables;
public:
    Node* tree;
    void print_recursive(Node*, size_t);
    void print();
    void recursive_free(Node*);
    Tree()
    {
        tree = nullptr;
    }
    ~Tree() 
    {
        if(tree != nullptr)
            recursive_free(tree);
    }
};