#pragma once
#include "Variable.h"
#include <algorithm>
#include <vector>
#include <iostream>

class variable_table
{
private:
    // ������ ���������� �� ����������
    vector<Variable*> _vars;

public:
    // ����������� ��-���������
    variable_table() = default;
    // ����������
    ~variable_table();
    // �������� ����� ��� ���������� ���������� � �������
    void add_variable(Variable*);
    void remove_variable(string);
    Variable* get_variable_by_name(const string&);
    bool has_variable(const string&);
};

