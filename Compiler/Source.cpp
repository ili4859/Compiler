#include "Token.h"
#include "Lexer.h"
#include <iostream>
#include <string>
#include <fstream>
#include "Parser.h"

int main() 
{                     // 0                1                   2               3               4
	string files[] = { "input.txt", "inputarifmetic.txt", "inputfor.txt", "inputif.txt", "inputwhile.txt" };
	try
	{
		Parser pars("io\\" + files[2]);
		pars.parse();
	}
	catch (exception e) { std::cout << e.what(); };
	return 0;
}