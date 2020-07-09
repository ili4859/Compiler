#pragma once
#include <string>
#include <vector>
using namespace std;
//Типы узлов
enum class Node_type 
{
    VARIABLE,
    PROG,                    // тип начального узла всей программы
    EXPR,                    // тип начального узла, в котором будет все выражение
    CONSTANT,                // любое число
    CONSTANT_VARIABLE,       // константная переменная
    ADD,                     // сложение
    SUB,                     // вычитание
    MUL,                     // умножение
    DIV,                     // деление
    VARIABLE_DECLARATION,    // объявление переменной
    CONSTANT_VARIABLE_DECLARATION,    // объявление переменной
    USING_VARIABLE,          // использование переменной
    USING_CONSTANT_VARIABLE,          // использование переменной
    SET,                     // равно
    VARIABLE_TYPE,            // тип перемененной
    LESS,
    MORE,
    EQUIVALENT,
    IF,
    ELSE,
    THEN,
    WHILE,
    FOR,
    IN,
    PRINT
};

class Node 
{
public:
    std::string value;
    Node_type type;
    vector<Node*> rNode;
    Node(Node_type type, const std::string& value = "")
    {
        this->type = type;
        this->value = value;
    }
};