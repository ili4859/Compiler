#include "Lexer.h"

void Lexer::Split() {
   // временная переменная, куда будут добавляться символы, до тех пор пока не найдется 
   // разделитель
    string temp_token;
    // идем по всем символам строки
    for (char symbol : _code) {
        // проверяем, является ли текущий токен разделителем
        if (Is_Split_Symbol(symbol)) {
            // если да

            // если текущий токен не пуст
            if (!temp_token.empty()) {
                // создаем новый токен, передавая в качестве параметра временную переменную
                Token* new_token = new Token(temp_token);

                // и добавляем его в массив
                _tokens.push_back(new_token);

                // и очищаем временную переменную, так как токен закончился
                temp_token.clear();
            }

            // если символ не пробел
            if (symbol != ' ' && symbol != '\t') 
            {
                if (symbol == '=' && !_tokens.empty() && _tokens.back()->Get_Lexem() == "=")
                {

                    _tokens.pop_back();
                    Token* tok = new Token("==");
                    _tokens.push_back(tok);
                }
                else {
                    // значит это разделитель, который является токеном
                    string symbol_token(1, symbol);

                    // создаем новый токен, передавая в качестве параметра строку из символа
                    Token* new_token = new Token(symbol_token);

                    // и добавляем его в массив
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

    // после того как прошли все символы, добавляем токен в массив, если он не пуст
    if (!temp_token.empty()) {
        // создаем новый токен, передавая в качестве параметра строку из символа
        Token* new_token = new Token(temp_token);

        // и добавляем его в массив
        _tokens.push_back(new_token);

        // и очищаем временную переменную, так как токен закончился
        temp_token.clear();
    }
    Token* tok = new Token("ENDF");
    _tokens.push_back(tok);
}

// функция возвращающая true если переданный символ является разделителем
bool Lexer::Is_Split_Symbol(char symbol) {
    // здесь мы проверяем, если символ равен хоть одному из этих символов, значит он разделитель
    return  symbol == '+' || symbol == '-' ||
        symbol == '/' || symbol == '*' || symbol == '>' || symbol == '<' ||
        symbol == '(' || symbol == ')' ||
        symbol == ' ' || symbol == '=' || symbol == ':' || symbol == '\n' || symbol == '{'
        || symbol == '}'|| symbol == '\t';
}

void Lexer::Print() {
    // проходим по всем токенам
    for (const auto& token : _tokens) {
        // и выводим их
        cout << token->Get_Lexem() << " " << "\t\twith type:" << (int)token->Get_Type() << endl;
    }
}

// функция сдвигающая индекс текущего токена на 1 вперед
void  Lexer:: next_token() {
    // проверяем, чтобы не выйти за пределы массива токенов
    if (_current_token_index < _tokens.size() - 1)
    {
        ++_current_token_index;
    }
}

// функция возвращающая тип текущего токена
token_type Lexer::current_token_type() {
    return _tokens[_current_token_index]->Get_Type();
}

// функция возвращающая текущий токен
Token Lexer::current_token() {
    return *_tokens[_current_token_index];
}