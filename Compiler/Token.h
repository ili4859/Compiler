#pragma once
#include <string>
#include <set>
using namespace std;

//Типы токенов
enum class token_type {
	NONE,                    // неопред.
	NUMBER,                  // число
    PLUS,                    // +
    MINUS,                   // -
    STAR,                    // *
    SLASH,                   // /
    LPAR,                    // (
    RPAR,                    // )
    EQUAL,                   // =
    VARIABLE,
    VARIABLE_TYPE,
    VARIABLE_DECLARATION,
    COLON,                   // :
    ENDL,                    // \n
    ENDF,                    //eof
    IF,                      //if
    ELSE,                    //else
    FOR,                     //for
    IN,
    WHILE,                   //while
    OPEN,                    //{
    CLOSE,                   //}
    MORE,                    // >
    LESS,                    // <
    DOTS,                   // ...
    EQUIVALENT,               // ==
    PRINT
};

//сеты используемых слов
const set<string> declaration_words = {"var", "let"};
const set<string> type_words = { "Int"/*,"Float" ,"Double" ,"Bool"*/ };
const set<string> special_words = {"for", "if", "else", "while", "in", "print" };

class Token{
private: 
    string _lexem;
    token_type _type;
    static bool Is_Number(const string&);
    static bool Is_Word(const string&);
    static bool Is_Declaration(const string&);
    static bool Is_Funk(const string&);
    static bool Is_VariableType(const string&);
public:
    static token_type Which_Type_Of_Lexeme(const string&);
    Token(const string& lexeme) {
        this->_lexem = lexeme;
        // вызываем функцию, которая по лексеме возвратит ее тип
        this->_type = Which_Type_Of_Lexeme(lexeme);
    }
    string Get_Lexem()
    {
        return _lexem; 
    }
    token_type Get_Type()
    {
        return _type;
    }
};
