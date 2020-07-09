#pragma once
#include "Variable.h"
#include <algorithm>
#include <vector>
#include <iostream>

class variable_table
{
private:
    // массив указателей на переменную
    vector<Variable*> _vars;

public:
    // конструктор по-умолчанию
    variable_table() = default;
    // деструктор
    ~variable_table();
    // основной метод для добавления переменных в таблицу
    void add_variable(Variable*);
    void remove_variable(string);
    Variable* get_variable_by_name(const string&);
    bool has_variable(const string&);
};

