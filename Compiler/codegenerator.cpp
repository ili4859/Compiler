#include "codegenerator.h"

void codegenerator::preparefile()
{
	filedata.open("io\\data.txt", std::ios_base::out);
	if (!filedata)
		throw runtime_error("Can not create file");
	
	filecode.open("io\\code.txt", std::ios_base::out);
	if (!filecode)
		throw runtime_error("Can not create file");
	
}

void codegenerator::writenode(Node* node)
{
	switch (node->type)
	{
	case (Node_type::PROG):
	case (Node_type::THEN):
	{
		for (auto i : node->rNode)
			writenode(i);
		break;
	}
	case (Node_type::IF):
	{
		writeif(node);
		break;
	}
	case (Node_type::FOR):
	{
		writefor(node);
		break;
	}
	case (Node_type::WHILE):
	{
		writewhile(node);
		break;
	}
	case (Node_type::SET):
	{
		writeset(node);
		break;
	}
	case (Node_type::PRINT):
	{
		writeprint(node);
		break;
	}
	case (Node_type::VARIABLE_DECLARATION):
	{
		string code;
		code = node->value + " dd ?\n";
		addvariable(code);
		break;
	}
	default:
		break;
	}
}

void codegenerator::writeif(Node* node)
{
	string code;
	int temp = countif;
	countif++;
	auto i = node->rNode[0];
	if (i->type == Node_type::LESS)
	{
		writecondidion(i, "jge", ("if_else_"+ to_string(temp)));
	}
	if (i->type == Node_type::MORE)
	{
		writecondidion(i, "jle", ("if_else_" + to_string(temp)));
	}
	if (i->type == Node_type::EQUIVALENT)
	{
		writecondidion(i, "jnz", ("if_else_" + to_string(temp)));
	}
	if (i->type == Node_type::VARIABLE)
	{
		getoperand(i, "");
		code = "pop eax\n";
		code += "cmp eax, 0\n";
		code +=  "jz if_else_" + to_string(temp);
		code += "\n";
		addcode(code);
	}
	i = node->rNode[1];
	writenode(i);
	code.clear();
	code += "if_else_" + to_string(temp);
	code +=":\n";
	addcode(code);
	if (node->rNode.size() == 3)
	{
		writenode(node->rNode[2]->rNode[0]);
	}
	code.clear();
	code = "if_end_" + to_string(temp) + ":\n";
	addcode(code);
}

void codegenerator::writewhile(Node* node)
{
	int temp = countwhile++;
	string code;
	code = "while_begin_" + to_string(temp) + ":\n";
	addcode(code);
	auto i = node->rNode[0];
	if (i->type == Node_type::LESS)
	{
		writecondidion(i, "jge", ("while_end_" + to_string(temp)));
	}
	if (i->type == Node_type::MORE)
	{
		writecondidion(i, "jle", ("while_end_" + to_string(temp)));
	}
	if (i->type == Node_type::EQUIVALENT)
	{
		writecondidion(i, "jnz", "while_end_" + to_string(temp));
	}
	if (i->type == Node_type::VARIABLE)
	{
		getoperand(i, "");
		code = "pop eax\n";
		code += "cmp eax, 0\n";
		code += "jz while_end_" + to_string(temp) + "\n";
		code += "\n";
		addcode(code);
	}
	writenode(node->rNode[1]);
	code.clear();
	code = "jmp while_begin_" + to_string(temp) + "\n";
	code += "while_end_" + to_string(temp) + ":\n";
	addcode(code);
}

void codegenerator::writefor(Node* node)
{
	int temp = countfor++;
	string code;
	if (varfor.find(node->rNode[0]->value) == varfor.end())
	{
		varfor.insert(node->rNode[0]->value);
		code = node->rNode[0]->value + " dd 0\n";
		addvariable(code);
	}
	code.clear();
	getoperand(node->rNode[1]->rNode[0], "");
	getoperand(node->rNode[1]->rNode[1], "");	
	code += "pop eax\n";
	code += "pop ebx\n";
	code += + "mov " + node->rNode[0]->value + ", ebx\n";
	code += "for_begin_" + to_string(temp) + ":\n";
	code += "mov edx, " + node->rNode[0]->value + "\n";
	code += "mov eax, " + node->rNode[1]->rNode[1]->value + "\n";
	code += "cmp edx, eax\n";
	code += "jg for_end_" + to_string(temp) + "\n";
	addcode(code);
	code.clear();
	writenode(node->rNode[2]);
	code = "add " + node->rNode[0]->value + ", 1\n";
	code += "jmp for_begin_" + to_string(temp) + "\n";
	code += "for_end_" + to_string(temp) + ":\n";
	addcode(code);
}

void codegenerator::writeprint(Node* node)
{	
	getoperand(node->rNode[0], "");
	string temp;
	temp = "pop eax\n";
	temp += "invoke  crt_printf, ADDR tpt, eax\n";
	addcode(temp);
}

void codegenerator::writeset(Node* node)
{
	string code;
	if (node->rNode[0]->type == Node_type::CONSTANT_VARIABLE_DECLARATION)
	{
		if (node->rNode[1]->type == Node_type::USING_CONSTANT_VARIABLE
			|| node->rNode[1]->type == Node_type::USING_VARIABLE
			|| node->rNode[1]->type == Node_type::CONSTANT)
		{
			code = node->rNode[0]->value + " equ ";
			code += node->rNode[1]->value + "\n";
		}
		else
		{
			string str;
			if (node->rNode[1]->type == Node_type::ADD)
				str = "add";
			if (node->rNode[1]->type == Node_type::MUL)
				str = "mul";
			if (node->rNode[1]->type == Node_type::SUB)
				str = "sub";
			if (node->rNode[1]->type == Node_type::DIV)
				str = "div";
			writeoperation(node->rNode[1], str, "");
			code = "pop eax\n";
			code += node->rNode[0]->value + " equ eax\n";
		}	
	}else if (node->rNode[0]->type == Node_type::VARIABLE_DECLARATION)
	{
		code = node->rNode[0]->value + " dd 0\n";
		addvariable(code);

		if (isvariable(node->rNode[1]->type))
		{
			code = "mov eax, " + node->rNode[1]->value + "\n";
			code += "mov " + node->rNode[0]->value + ", eax\n";
		}
		else
		{
			string str;
			if (node->rNode[1]->type == Node_type::ADD)
				str = "add";
			if (node->rNode[1]->type == Node_type::MUL)
				str = "mul";
			if (node->rNode[1]->type == Node_type::SUB)
				str = "sub";
			if (node->rNode[1]->type == Node_type::DIV)
				str = "div";
			writeoperation(node->rNode[1], str, "");
			code = "pop eax\n";
			code += "mov " + node->rNode[0]->value + ", eax\n";
		}
	}
	else
	{
		if (isvariable(node->rNode[1]->type))
		{
			code = "mov eax, " + node->rNode[1]->value + "\n";
			code += "mov " + node->rNode[0]->value + ", eax\n";
		}
		else
		{
			string str;
			if (node->rNode[1]->type == Node_type::ADD)
				str = "add";
			if (node->rNode[1]->type == Node_type::MUL)
				str = "mul";
			if (node->rNode[1]->type == Node_type::SUB)
				str = "sub";
			if (node->rNode[1]->type == Node_type::DIV)
				str = "div";
			writeoperation(node->rNode[1], str, "");
			code = "pop eax\n";
			code += "mov " + node->rNode[0]->value + ", eax\n";
		}
	}
	addcode(code);
}

void codegenerator::writecondidion(Node* node, string operation, string jumppoint)
{
	string code;
	auto i = node->rNode[0];
	getoperand(i, "");
	i = node->rNode[1];
	getoperand(i, "");
	code =  "pop eax\n";
	code += "pop ebx\n";
	code += "cmp ebx, eax\n";
	code += operation + " " + jumppoint + "\n";
	addcode(code);
}

void codegenerator::writeoperation(Node* node, string nameoperation, string reg)
{
	if (nameoperation == "div")
	{
		divoperation(node);
		return;
	}
	const string temp = "registr";
	auto i = node->rNode[0];
	getoperand(i, temp); 
	i = node->rNode[1];
	getoperand(i, temp);
	string code;
	code = "pop eax\n";
	code += "pop ebx\n";
	code += nameoperation + " ebx, eax\n";
	code += "push ebx\n";
	addcode(code);
}

bool codegenerator::isvariable(Node_type i)
{
	return i == Node_type::USING_CONSTANT_VARIABLE || i == Node_type::CONSTANT || i == Node_type::USING_VARIABLE;
}

void codegenerator::getoperand(Node* i, string registr = "")
{
	string code;
	if (isvariable(i->type))
	{
		code = "push " +  i->value + "\n";
	}
	if (i->type == Node_type::ADD)
	{
		writeoperation(i, "add", registr);
	}
	if (i->type == Node_type::SUB)
	{
		writeoperation(i, "sub", registr);
	}
	if (i->type == Node_type::MUL)
	{
		writeoperation(i, "imul", registr);
	}
	if (i->type == Node_type::DIV)
	{
		writeoperation(i, "div", registr);
	}
	addcode(code);
	return;
}

void codegenerator::addcode(string code)
{
	filecode << code << endl;
}

void codegenerator::addvariable(string str)
{
	filedata << str;
}

void codegenerator::divoperation(Node* node)
{
	const string temp = "registr";
	auto i = node->rNode[0];
	getoperand(i, temp);
	i = node->rNode[1];
	getoperand(i, temp);
	string code;
	code = "pop ecx\n";
	code += "pop eax\n";
	code += "xor ebx, ebx\n";
	code += "cdq\n";
	code += "div ecx\n";
	code += "push eax\n";
	addcode(code);
}

void codegenerator::avtobotiojedeniemsja()
{
	file.open("io\\output.asm", std::ios_base::out);
	file << ".386\n.model flat, stdcall\n";
	file << "option casemap :none\ninclude \\masm32\\include\\windows.inc\ninclude \\masm32\\include\\masm32.inc\ninclude \\masm32\\include\\msvcrt.inc\ninclude \\masm32\\macros\\macros.asm\nincludelib \\masm32\\lib\\masm32.lib\nincludelib \\masm32\\lib\\msvcrt.lib\n";
	file << "\n.data\n";
	file << "tpt db '%d ',0\n";
	filedata.close();
	filedata.open("io\\data.txt", std::ios_base::in);
	while (!filedata.eof())
	{
		string temp;
		getline(filedata, temp);
		temp += "\n";
		file << temp;
	}
	file << "\n";
	file << ".code\nstart :\n";
	filecode.close();
	filecode.open("io\\code.txt", std::ios_base::in);
	while (!filecode.eof())
	{
		string temp;
		getline(filecode, temp);
		temp += "\n";
		file << temp;
	}
	file << "\nend start";
	file.close();
	filedata.close();
	filecode.close();
	remove("io\\code.txt");
	remove("io\\data.txt");
}

codegenerator::codegenerator(Node* node)
{
	this->node = node;
}

void codegenerator::generate()
{
	preparefile();
	writenode(node);
	avtobotiojedeniemsja();
}
