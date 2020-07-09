#include "Lexer.h"

void Lexer::Split() {
   // ��������� ����������, ���� ����� ����������� �������, �� ��� ��� ���� �� �������� 
   // �����������
    string temp_token;
    // ���� �� ���� �������� ������
    for (char symbol : _code) {
        // ���������, �������� �� ������� ����� ������������
        if (Is_Split_Symbol(symbol)) {
            // ���� ��

            // ���� ������� ����� �� ����
            if (!temp_token.empty()) {
                // ������� ����� �����, ��������� � �������� ��������� ��������� ����������
                Token* new_token = new Token(temp_token);

                // � ��������� ��� � ������
                _tokens.push_back(new_token);

                // � ������� ��������� ����������, ��� ��� ����� ����������
                temp_token.clear();
            }

            // ���� ������ �� ������
            if (symbol != ' ' && symbol != '\t') 
            {
                if (symbol == '=' && !_tokens.empty() && _tokens.back()->Get_Lexem() == "=")
                {

                    _tokens.pop_back();
                    Token* tok = new Token("==");
                    _tokens.push_back(tok);
                }
                else {
                    // ������ ��� �����������, ������� �������� �������
                    string symbol_token(1, symbol);

                    // ������� ����� �����, ��������� � �������� ��������� ������ �� �������
                    Token* new_token = new Token(symbol_token);

                    // � ��������� ��� � ������
                    _tokens.push_back(new_token);
                }
            } 
        }
        else {
            if (symbol == '.' && !temp_token.empty() && temp_token[temp_token.size() - 1] == '.')
            {
                if (temp_token == "..")
                {
                    temp_token.clear();
                    Token* tok = new Token("...");
                    _tokens.push_back(tok);
                }
                else if (temp_token != "...")
                {
                    string strtemp = temp_token.substr(0, temp_token.size() - 1);
                    Token* tok1 = new Token(strtemp);
                    _tokens.push_back(tok1);
                    temp_token = "..";
                }

            }
            else
            {
                temp_token += symbol;
            }
        }
    }

    // ����� ���� ��� ������ ��� �������, ��������� ����� � ������, ���� �� �� ����
    if (!temp_token.empty()) {
        // ������� ����� �����, ��������� � �������� ��������� ������ �� �������
        Token* new_token = new Token(temp_token);

        // � ��������� ��� � ������
        _tokens.push_back(new_token);

        // � ������� ��������� ����������, ��� ��� ����� ����������
        temp_token.clear();
    }
    Token* tok = new Token("ENDF");
    _tokens.push_back(tok);
}

// ������� ������������ true ���� ���������� ������ �������� ������������
bool Lexer::Is_Split_Symbol(char symbol) {
    // ����� �� ���������, ���� ������ ����� ���� ������ �� ���� ��������, ������ �� �����������
    return  symbol == '+' || symbol == '-' ||
        symbol == '/' || symbol == '*' || symbol == '>' || symbol == '<' ||
        symbol == '(' || symbol == ')' ||
        symbol == ' ' || symbol == '=' || symbol == ':' || symbol == '\n' || symbol == '{'
        || symbol == '}'|| symbol == '\t';
}

void Lexer::Print() {
    // �������� �� ���� �������
    for (const auto& token : _tokens) {
        // � ������� ��
        cout << token->Get_Lexem() << " " << "\t\twith type:" << (int)token->Get_Type() << endl;
    }
}

// ������� ���������� ������ �������� ������ �� 1 ������
void  Lexer:: next_token() {
    // ���������, ����� �� ����� �� ������� ������� �������
    if (_current_token_index < _tokens.size() - 1)
    {
        ++_current_token_index;
    }
}

// ������� ������������ ��� �������� ������
token_type Lexer::current_token_type() {
    return _tokens[_current_token_index]->Get_Type();
}

// ������� ������������ ������� �����
Token Lexer::current_token() {
    return *_tokens[_current_token_index];
}