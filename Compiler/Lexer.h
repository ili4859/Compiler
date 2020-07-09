#pragma once
#include "Token.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class Lexer {
private:
    string _code; // ���������� � ������� ����� �������� ���� ���
    vector<Token*> _tokens; // ������ �������
    int _current_token_index;
public:
    // ������� ������������ true ���� ���������� ������ �������� ������������
    static bool Is_Split_Symbol(char symbol);
    void Print();
    void Split();
    void next_token();
    token_type current_token_type();
    Token current_token();
    // ����������� ����������� ������ � �����
    Lexer(const string& code) {
        _current_token_index = 0;
        ifstream ifs(code);
        string str;
        while (ifs.good()) {
            getline(ifs, str);
            _code += str + " ";
        }
    }
    // ����������, ��������� ������ ��� ������
    ~Lexer() {
        _tokens.clear();
    }
};

