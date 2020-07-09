#pragma once
#include "Tree.h"
#include "Lexer.h"
#include "variable_table.h"
#include "codegenerator.h"
#include <iostream>

using namespace std;

class Parser 
{
private:
    // лексер
    Lexer* _lex;
    variable_table table;
    // AST
    Tree* _tree;
    static bool expresionHasVariable(string, Node*);
public:
    Parser(const string&);
    ~Parser();
    void parse();
    void error(const string&);
    Node* condition();
    Node* equal_expression();
    Node* program();
    Node* noteblock();
    Node* statement();
    Node* expression();
    Node* additive_expression();
    Node* multiplicative_expression();
    Node* primary_expression();
    Node* variable_expression();
    Node* parenthesized_expression();
    Node* number();
    Node* variable();
    Node* ifstatement();
    Node* range();
    Node* print();
};

