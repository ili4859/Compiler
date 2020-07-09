#pragma once
#include <string>
using namespace std;

//���� ����������
enum class variable_type{
    // ���� ��� �� ����������
    UNDEFINED = 0xffffff,

    Int = 0x003000,     //������������� ����������
    ConstInt = 0x004000,     //������������� ����������
    Float = 0x005000,   //���������� � ��������� �������
    ConstFloat = 0x006000,   //���������� � ��������� �������
    Double = 0x007000,  //
    ConstDouble = 0x008000,  //
    Bool = 0x009000,    //true false
    ConstBool = 0x010000,    //true false
};

class Variable {
private:
    // ��� ����������
    string _name;
    // � �� ���
    variable_type _type;
public:
    Variable(const string& variable_name, variable_type variable_type)
    {
        _name = variable_name;
        _type = variable_type;
    }
    string name()
    {
        return _name;
    }
    bool Is_Const();
    variable_type type()
    {
        return _type;
    }
};

variable_type string_to_var_type(string);