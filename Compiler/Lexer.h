#pragma once
#include "Token.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class Lexer {
private:
    string _code; // переменная в которой будет хранится весь код
    vector<Token*> _tokens; // массив токенов
    int _current_token_index;
public:
    // функция возвращающая true если переданный символ является разделителем
    static bool Is_Split_Symbol(char symbol);
    void Print();
    void Split();
    void next_token();
    token_type current_token_type();
    Token current_token();
    // конструктор принимающий строку с кодом
    Lexer(const string& code) {
        _current_token_index = 0;
        ifstream ifs(code);
        string str;
        while (ifs.good()) {
            getline(ifs, str);
            _code += str + " ";
        }
    }
    // деструктор, очищающий память под токены
    ~Lexer() {
        _tokens.clear();
    }
};

