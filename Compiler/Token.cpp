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
    // ��������� ������ ��������� �������
    // ���� ��� �����
    if (Is_Number(lexeme))
        return token_type::NUMBER;
    // ���� +
    if (lexeme == "+")
        return token_type::PLUS;
    if (lexeme == "in")
        return token_type::IN;
    // ���� -    
    if (lexeme == "-")
        return token_type::MINUS;
    // ���� *
    if (lexeme == "...")
        return token_type::DOTS;
    if (lexeme == "*")
        return token_type::STAR;
    // ���� /
    if (lexeme == "/")
        return token_type::SLASH;
    // ���� (
    if (lexeme == "(")
        return token_type::LPAR;
    // ���� )
    if (lexeme == ")")
        return token_type::RPAR;   
    // ���� =
    if (lexeme == "=")
        return token_type::EQUAL;  
    // ���� ������� �� ����� ������
    if (lexeme == "\n")
        return token_type::ENDL;  
    // ���� :
    if (lexeme == ":")
        return token_type::COLON; 
    // ���� ����� �����
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
    // ��-��������� ������������ �������������� ���
    return token_type::NONE;
}

