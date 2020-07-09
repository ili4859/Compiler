#pragma once
#include <string>
using namespace std;

//Типы переменных
enum class variable_type{
    // если тип не установлен
    UNDEFINED = 0xffffff,

    Int = 0x003000,     //Целочисленная переменная
    ConstInt = 0x004000,     //Целочисленная переменная
    Float = 0x005000,   //Переменные с плавающей запятой
    ConstFloat = 0x006000,   //Переменные с плавающей запятой
    Double = 0x007000,  //
    ConstDouble = 0x008000,  //
    Bool = 0x009000,    //true false
    ConstBool = 0x010000,    //true false
};

class Variable {
private:
    // имя переменной
    string _name;
    // и ее тип
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