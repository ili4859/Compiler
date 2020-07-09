#include "Token.h"

bool Token::Is_Number(const string& lexem) {
    if (!isdigit(lexem[0]))
        return false;
   // bool hasDot = false;
    for (const auto& s : lexem)
    {
        if (!isdigit(s))
        {
          //  if (s == '.' && !hasDot)
          //      hasDot = true;
          //  else
                return false;
        }
    }
    return true;
}

bool Token::Is_Word(const string& lexem) {
    
    if (lexem[0] != '_' && !isalpha(lexem[0]))
    {
        return false;
    }
    for (const auto& s : lexem)
    {
        if (!isalnum(s) && s != '_')
            return false;
    }
    if (special_words.find(lexem) != special_words.end())
    {
        return false;
    }
    else if (declaration_words.find(lexem) != declaration_words.end())
    {
        return false;
    }
    return true;
}

bool Token::Is_Declaration(const string& lexem)
{
    return (declaration_words.find(lexem) != declaration_words.end());
}

bool Token::Is_Funk(const string& lexem)
{
    return (special_words.find(lexem) != special_words.end());;
}

bool Token::Is_VariableType(const string& lexem)
{
    return (type_words.find(lexem) != type_words.end());
}

token_type Token::Which_Type_Of_Lexeme(const string& lexeme) {
    // описываем каждую возможную лексему
    // если это число
    if (Is_Number(lexeme))
        return token_type::NUMBER;
    // если +
    if (lexeme == "+")
        return token_type::PLUS;
    if (lexeme == "in")
        return token_type::IN;
    // если -    
    if (lexeme == "-")
        return token_type::MINUS;
    // если *
    if (lexeme == "...")
        return token_type::DOTS;
    if (lexeme == "*")
        return token_type::STAR;
    // если /
    if (lexeme == "/")
        return token_type::SLASH;
    // если (
    if (lexeme == "(")
        return token_type::LPAR;
    // если )
    if (lexeme == ")")
        return token_type::RPAR;   
    // если =
    if (lexeme == "=")
        return token_type::EQUAL;  
    // если переход на новую строку
    if (lexeme == "\n")
        return token_type::ENDL;  
    // если :
    if (lexeme == ":")
        return token_type::COLON; 
    // если конец файла
    if (lexeme == "ENDF")
        return token_type::ENDF;  
    if (lexeme == "if")
        return token_type::IF;  
    if (lexeme == "for")
        return token_type::FOR;  
    if (lexeme == "else")
        return token_type::ELSE;  
    if (lexeme == "while")
        return token_type::WHILE;  
    if (lexeme == "{")
        return token_type::OPEN;  
    if (lexeme == "}")
        return token_type::CLOSE;  
    if (lexeme == "<")
        return token_type::LESS;  
    if (lexeme == ">")
        return token_type::MORE;
    if (lexeme == "print")
        return token_type::PRINT;
    if (lexeme == "==")
        return token_type::EQUIVALENT;  
    if (Is_VariableType(lexeme))
        return token_type::VARIABLE_TYPE;    
    if (Is_Declaration(lexeme)) 
        return token_type::VARIABLE_DECLARATION;
    if (Is_Word(lexeme))
        return token_type::VARIABLE;
    // по-умолчанию возвращается нераспознанный тип
    return token_type::NONE;
}

