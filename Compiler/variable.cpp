#include "variable.h"

variable_type string_to_var_type(string str)
{
	if (str == "Int") 
		return variable_type::Int;
	if (str == "Float")
		return variable_type::Float;
	if (str == "Double") 
		return variable_type::Double;
	if (str == "Bool")
		return variable_type::Bool;
	if (str == "ConstInt")
		return variable_type::ConstInt;
	if (str == "ConstFloat")
		return variable_type::ConstFloat;
	if (str == "ConstDouble")
		return variable_type::ConstDouble;
	if (str == "ConstBool")
		return variable_type::ConstBool;
	return variable_type::UNDEFINED;
}

bool Variable::Is_Const()
{
	if (variable_type::ConstBool == _type)
		return true;
	if (variable_type::ConstDouble == _type)
		return true;
	if (variable_type::ConstFloat == _type)
		return true;
	if (variable_type::ConstInt == _type)
		return true;
	return false;
}
