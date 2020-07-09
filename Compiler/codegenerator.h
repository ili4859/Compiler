#pragma once
#include "Node.h"
#include <fstream>
#include <iostream>
#include <set>

class codegenerator
{
private:
	set<string> varfor;
	int countfor = 0;
	int countif = 0;
	int countwhile = 0;
	fstream file;
	fstream filedata;
	fstream filecode;
	Node* node;
	void addcode(string);
	bool isvariable(Node_type);
	void preparefile();
	void writenode(Node*);
	void writeif(Node*);
	void writewhile(Node*);
	void writefor(Node*);
	void writeprint(Node*);
	void writeset(Node*);
	void writecondidion(Node*, string, string);
	void writeoperation(Node*, string, string);
	void getoperand(Node*, string);
	void addvariable(string);
	void divoperation(Node*);
	void avtobotiojedeniemsja();
public:
	codegenerator(Node*);
	void generate();
};

