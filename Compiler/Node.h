#pragma once
#include <string>
#include <vector>
using namespace std;
//���� �����
enum class Node_type 
{
    VARIABLE,
    PROG,                    // ��� ���������� ���� ���� ���������
    EXPR,                    // ��� ���������� ����, � ������� ����� ��� ���������
    CONSTANT,                // ����� �����
    CONSTANT_VARIABLE,       // ����������� ����������
    ADD,                     // ��������
    SUB,                     // ���������
    MUL,                     // ���������
    DIV,                     // �������
    VARIABLE_DECLARATION,    // ���������� ����������
    CONSTANT_VARIABLE_DECLARATION,    // ���������� ����������
    USING_VARIABLE,          // ������������� ����������
    USING_CONSTANT_VARIABLE,          // ������������� ����������
    SET,                     // �����
    VARIABLE_TYPE,            // ��� ������������
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