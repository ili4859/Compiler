#include "Tree.h"
#include <iostream>
using namespace std;

void Tree::print_recursive(Node* current_node, size_t level) {
    // если узел не существует, то просто выходим из функции
    if (current_node == nullptr)
        return;


    for (int i = 0; i < level; ++i) {
        // выводим level раз отступ в два пробела
        cout << "  ";
    }

    // выводим обозначение узла
    cout << "+-";

    // в зависимости от типа узла
    // выводим нужное
    switch (current_node->type)
    {
    case Node_type::VARIABLE:
    {
        cout << "VARIABLE ";
        cout << "(" << current_node->value << ")";
        break;
    }
    case Node_type::ELSE:
    {
        cout << "ELSE ";
        break;
    }
    case Node_type::PRINT:
    {
        cout << "PRINT ";
        break;
    }
    case Node_type::WHILE:
    {
        cout << "WHILE ";
        break;
    }
    case Node_type::THEN:
    {
        cout << "DO ";
        break;
    }
    case Node_type::EQUIVALENT:
    {
        cout << "EQUIVALENT ";
        break;
    }
    case Node_type::IN:
    {
        cout << "IN ";
        break;
    }
    case Node_type::FOR:
    {
        cout << "FOR ";
        break;
    }
    case Node_type::LESS:
    {
        cout << "LESS ";
        break;
    }
    case Node_type::MORE:
    {
        cout << "MORE ";
        break;
    }
    case Node_type::IF:
    {
        cout << "IF ";
        break;
    }
    case Node_type::PROG:
    {
        cout << "PROG ";
        break;
    }
    case Node_type::VARIABLE_DECLARATION:
    {
        cout << "VARIABLE_DECLARATION ";
        cout << "(" << current_node->value << ")"; 
        break;
    }
    case Node_type::USING_VARIABLE:
    {
        cout << "USING_VARIABLE ";
        cout << "(" << current_node->value << ")";
        break;
    }
    case Node_type::CONSTANT_VARIABLE_DECLARATION:
    {
        cout << "CONSTANT_VARIABLE_DECLARATION ";
        cout << "(" << current_node->value << ")"; 
        break;
    }
    case Node_type::USING_CONSTANT_VARIABLE:
    {
        cout << "USING_CONSTANT_VARIABLE ";
        cout << "(" << current_node->value << ")";
        break;
    }
    case Node_type::EXPR:
    {
        cout << "EXPR ";
        break;
    }
    case Node_type::CONSTANT:
    {
        cout << "CONST ";

        // так как константа имеет значение, то выводим его  в скобках
        cout << "(" << current_node->value << ")";
        break;
    }
    case Node_type::ADD:
    {
        cout << "ADD ";
        break;
    }
    case Node_type::SUB:
    {
        cout << "SUB ";
        break;
    }
    case Node_type::MUL:
    {
        cout << "MUL ";
        break;
    }
    case Node_type::DIV:
    {
        cout << "DIV ";
        break;
    }  
    case Node_type::SET:
    {
        cout << "SET ";
        break;
    }
    case Node_type::VARIABLE_TYPE:
    {
        cout << "VARIABLE_TYPE ";
        cout << "(" << current_node->value << ")";
        break;
    }
    }
    cout << endl;
    for (auto i : current_node->rNode)
    {
        print_recursive(i, level + 1);
    }
}

void Tree::print() {
    // первым параметром мы передаем вершину дерева, а вторым нулевой уровень
    // с которого мы начинаем
    print_recursive(tree, 0);
}

void Tree::recursive_free(Node* n)
{
    for (auto i : n->rNode)
    {
        recursive_free(i);
    }
    delete n;
}
