#include "variable_table.h"

variable_table::~variable_table()
{
    // ������� ������, ��� ����� ���������� ������ ��� ��������� ��� ����������
    _vars.clear();
}

// �������� ����� ��� ���������� ���������� � �������
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
    // �������� �� ������� ����������
    for (auto& variable : _vars)
    {
        // ���� ��� ���������� ��������� � ����������� ������
        if (variable->name() == name)
        {
            // �� ��������� ��� ����������
            return variable;
        }
    }

    // � ������, ���� ���������� ���, ���������� ����������
    throw std::logic_error("Variable not found!");
}

bool variable_table::has_variable(const string& name)
{
    // �������� �� ������� ����������
    for (auto& variable : _vars)
    {
        // ���� ��� ���������� ��������� � ����������� ������
        if (variable->name() == name)
        {
            // �� ��������� ������
            return true;
        }
    }

    // � ������, ���� ���������� ��� ��������� false
    return false;
}
