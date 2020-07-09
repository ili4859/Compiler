#include "variable_table.h"

variable_table::~variable_table()
{
    // очищаем массив, тем самым освобождая память под указатели под переменные
    _vars.clear();
}

// основной метод для добавления переменных в таблицу
void variable_table::add_variable(Variable* var)
{
    _vars.push_back(var);
}

void variable_table::remove_variable(std::string var)
{
    for (vector<Variable*>::iterator i = _vars.begin(); i != _vars.end(); i++)
    {
        if ((*i)->name() == var)
        {
            _vars.erase(i);
            return;
        }
    }
}

Variable* variable_table::get_variable_by_name(const string& name)
{
    // проходим по массиву переменных
    for (auto& variable : _vars)
    {
        // если имя переменной совпадает с необходимым именем
        if (variable->name() == name)
        {
            // то возращаем эту переменную
            return variable;
        }
    }

    // в случае, если переменной нет, возбуждаем исключение
    throw std::logic_error("Variable not found!");
}

bool variable_table::has_variable(const string& name)
{
    // проходим по массиву переменных
    for (auto& variable : _vars)
    {
        // если имя переменной совпадает с необходимым именем
        if (variable->name() == name)
        {
            // то возращаем истину
            return true;
        }
    }

    // в случае, если переменной нет возращаем false
    return false;
}
