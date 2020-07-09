#include "Parser.h"

bool Parser::expresionHasVariable(string str, Node* n)
{
    if (n == nullptr)
        return false;
    bool has = (n->type == Node_type::USING_VARIABLE && n->value == str);
    for (auto i : n->rNode)
    {
        has = has || expresionHasVariable(str, i);
    }
    return has;
}

Parser::Parser(const string& file_path)
{
    // инициализируем лексер
    _lex = new Lexer(file_path);
    // инициализируем AST
    _tree = new Tree();
}

Parser::~Parser()
{
    // удаляем
    delete _lex;
    delete _tree;
}

void Parser::parse()
{
    // не забудем вызвать метод у лексера, чтобы разбить исходный код
    _lex->Split();
    // вызываем первый нетерминал грамматики
    _tree->tree = program();
    // вызываем метод для распечатки полученного дерева
    _tree->print();

    codegenerator code(_tree->tree);
    code.generate();
}

void Parser::error(const string& message)
{
    // выводим общую информацию
    cout << "Parse error! " << message << " ";
    // выводим дополнительно текущий токен
    cout << "Current token: " << _lex->current_token().Get_Lexem() << endl;

    // возбуждаем исключение
    throw std::logic_error(message);
}

Node* Parser::condition()
{
    Node* cond = additive_expression();
    if (_lex->current_token_type() == token_type::MORE)
    {
        _lex->next_token();
        Node* moretemp = additive_expression();
        Node* more = new Node(Node_type::MORE, "");
        more->rNode.push_back(cond);
        more->rNode.push_back(moretemp);
        return more;
    }
    if (_lex->current_token_type() == token_type::LESS)
    {
        _lex->next_token();
        Node* lesstemp = additive_expression();
        Node* less = new Node(Node_type::LESS, "");
        less->rNode.push_back(cond);
        less->rNode.push_back(lesstemp);
        return less;
    }
    if (_lex->current_token_type() == token_type::EQUIVALENT)
    {
        _lex->next_token();
        Node* equivalenttemp = additive_expression();
        Node* equivalent = new Node(Node_type::EQUIVALENT, "");
        equivalent->rNode.push_back(cond);
        equivalent->rNode.push_back(equivalenttemp);
        return equivalent;
    }
    return cond;
}

Node* Parser::program()
{
    Node* rnode = new Node(Node_type::PROG, "");
    while (_lex->current_token_type() != token_type::ENDF) {
        rnode->rNode.push_back(statement());
    }
    return rnode;
}

Node* Parser::noteblock()
{
    Node* rnode = new Node(Node_type::THEN, "");
    if (_lex->current_token_type() != token_type::OPEN)
        throw runtime_error("Expected '{'");
    _lex->next_token();
    while (_lex->current_token_type() != token_type::CLOSE) {

        if (_lex->current_token_type() == token_type::ENDF)
            throw runtime_error("Expected '}'");
        rnode->rNode.push_back(statement());
    }
    _lex->next_token();
    return rnode;
}

Node* Parser::statement()
{
    if (_lex->current_token_type() == token_type::IF)
    {
        Node* ifstat =  ifstatement();
        return ifstat;
    }
    if (_lex->current_token_type() == token_type::WHILE)
    {
        _lex->next_token();
        Node* ifs = condition();
        Node* whiledo = noteblock();
        Node* temp = new Node(Node_type::WHILE, "");
        temp->rNode.push_back(ifs);
        temp->rNode.push_back(whiledo);
        return temp;
    }
    if (token_type::FOR == _lex->current_token_type())
    {
        _lex->next_token();
        Node* var = variable();
        if (var->type != Node_type::VARIABLE)
            throw runtime_error("Expected unused variable");
        table.add_variable(new Variable(var->value, variable_type::Int));
        if (_lex->current_token_type() != token_type::IN)
            throw runtime_error("Expected 'in'");
        _lex->next_token();
        Node* rangenode = range();
        Node* code = noteblock();
        table.remove_variable(var->value);
        Node* fornode = new Node(Node_type::FOR, "");
        fornode->rNode.push_back(var);
        fornode->rNode.push_back(rangenode);
        fornode->rNode.push_back(code);
        return fornode;
    }
    if (token_type::PRINT == _lex->current_token_type())
    {
        _lex->next_token();
        Node* temp = print();
        
        return temp;
    }
    Node* expression_node = expression();
    
    return expression_node; 
}

Node* Parser::equal_expression()
{
    Node* equal_expression = variable_expression();

    if (_lex->current_token_type() == token_type::EQUAL)
    {
        if (table.get_variable_by_name(equal_expression->value)->Is_Const() && Node_type::USING_CONSTANT_VARIABLE==equal_expression->type)
            throw runtime_error("Can not change constant variable");
        // если мы вошли в условие, значит необходимо сдвинуть текущий токен
        _lex->next_token();

        // вызываем метод согласно грамматике 
        Node* additive_temp = additive_expression();
        if (equal_expression->type == Node_type::VARIABLE_DECLARATION)
        {
            if (expresionHasVariable(equal_expression->value, additive_temp))
                throw runtime_error("Variable cant be equal to itself");
        }
        Node* new_node = new Node(Node_type::SET, "");
        new_node->rNode.push_back(equal_expression);
        new_node->rNode.push_back(additive_temp);
        // возвращаем полученный токен
        return new_node;
    }
        // если ни одно из условий не выполнено, то возвращаем результат
        // общего нетерминала
        return equal_expression;
}

Node* Parser::expression()
{
    Node* temp = equal_expression();
    if (_lex->current_token_type() == token_type::ENDL)
    {
        _lex->next_token();
    }
    return temp;
}

Node* Parser::additive_expression()
{
    // согласно грамматике вызываем multiplicative_expression
    Node* multiplicative_node = multiplicative_expression();

    // если текущий токен плюс
    if (_lex->current_token_type() == token_type::PLUS)
    {
        // если мы вошли в условие, значит необходимо сдвинуть текущий токен
        _lex->next_token();

        // вызываем метод согласно грамматике 
        Node* additive_temp_node = additive_expression();

        // создаем новый узел с типом сложение
        Node* new_node = new Node(Node_type::ADD, "");
        new_node->rNode.push_back(multiplicative_node);
        new_node->rNode.push_back(additive_temp_node);


        // возвращаем полученный токен
        return new_node;
    }
    // если текущий токен минус
    else if (_lex->current_token_type() == token_type::MINUS)
    {
        // если мы вошли в условие, значит необходимо сдвинуть текущий токен
        _lex->next_token();

        // вызываем метод согласно грамматике 
        Node* additive_temp_node = additive_expression();

        // создаем новый узел с типом вычитание
        Node* new_node = new Node(Node_type::SUB, "");
        new_node->rNode.push_back(multiplicative_node);
        new_node->rNode.push_back(additive_temp_node);
        // возвращаем полученный токен
        return new_node;
    }

    // если ни одно из условий не выполнено, то возвращаем результат
    // общего нетерминала
    return multiplicative_node;
}

Node* Parser::multiplicative_expression()
{
    // согласно грамматике вызываем primary_expression
    Node* primary_node = primary_expression();

    // если текущий токен звездочка
    if (_lex->current_token_type() == token_type::STAR)
    {
        // если мы вошли в условие, значит необходимо сдвинуть текущий токен
        _lex->next_token();

        // вызываем метод согласно грамматике 
        Node* multiplicative_temp_node = multiplicative_expression();

        // создаем новый узел с типом умножение
        Node* new_node = new Node(Node_type::MUL, "");
        new_node->rNode.push_back(primary_node);
        new_node->rNode.push_back(multiplicative_temp_node);

        // возвращаем полученный токен
        return new_node;
    }
    // если текущий токен слэш
    else if (_lex->current_token_type() == token_type::SLASH)
    {
        // если мы вошли в условие, значит необходимо сдвинуть текущий токен
        _lex->next_token();

        // вызываем метод согласно грамматике 
        Node* multiplicative_temp_node = multiplicative_expression();

        // создаем новый узел с типом деление, так как токен был знаком деления
        Node* new_node = new Node(Node_type::DIV, "");
        new_node->rNode.push_back(primary_node);
        new_node->rNode.push_back(multiplicative_temp_node);

        // возвращаем полученный токен
        return new_node;
    }

    // если ни одно из условий не выполнено, то возвращаем результат
    // общего нетерминала
    return primary_node;
}

Node* Parser::primary_expression()
{
    string temp = _lex->current_token().Get_Lexem();
    // если тип текущего токена — число
    if (_lex->current_token_type() == token_type::NUMBER)
    {
        // вызываем метод согласно грамматике
        Node* number_node = number();
        // возвращаем полученный результат
        return number_node;
    }
    else if (_lex->current_token_type() == token_type::VARIABLE)
    {
        Node* variable_node = variable();
        if (!table.has_variable(variable_node->value))
            throw runtime_error("Variable " + variable_node->value + " not exist");
        return variable_node;
    }
    // если — открывающаяся круглая скобка
    else if (_lex->current_token_type() == token_type::LPAR)
    {
        // вызываем метод согласно грамматике
        Node* parent_expression_node = parenthesized_expression();
        // возвращаем полученный результат
        return parent_expression_node;
    }

    // а если ничего из выше описанного, то возвращаем nullptr
    throw runtime_error("Expected value");
}

Node* Parser::variable_expression()
{
    bool pudge = false;
    string  declaration_type = _lex->current_token().Get_Lexem();
    if (_lex->current_token_type() == token_type::VARIABLE_DECLARATION)
    {
        _lex->next_token();
        pudge = true;
    }
    Node* variableN = variable();
    Node* temp;
    if (pudge)
    {
        if (table.has_variable(variableN->value))
            throw runtime_error("Variable "+ variableN->value+" already exist");
        

        if (_lex->current_token_type() != token_type::COLON)
            throw runtime_error("Expected ':'");
        _lex->next_token();
        
        if (_lex->current_token_type() != token_type::VARIABLE_TYPE)
            throw runtime_error("Expected variable type");
        Variable* var;
        Node* temptemp = new Node(Node_type::VARIABLE_TYPE, _lex->current_token().Get_Lexem());
        if (declaration_type == "var")
        {
            var = new Variable(variableN->value, string_to_var_type(_lex->current_token().Get_Lexem()));
            temp = new Node(Node_type::VARIABLE_DECLARATION, variableN->value);
        }
        else
        {
            var = new Variable(variableN->value,string_to_var_type("Const" + _lex->current_token().Get_Lexem()));
            temp = new Node(Node_type::CONSTANT_VARIABLE_DECLARATION, variableN->value);       
        }
        temp->rNode.push_back(temptemp);
        table.add_variable(var);
        _lex->next_token();
    }
    else
    {
        if (!table.has_variable(variableN->value))
            throw runtime_error("Variable " + variableN->value + " not exist");
        if (table.get_variable_by_name(variableN->value)->Is_Const())
            temp = new Node(Node_type::USING_CONSTANT_VARIABLE, variableN->value);
        else
            temp = new Node(Node_type::USING_VARIABLE, variableN->value);
    }
    return temp;
}

Node* Parser::parenthesized_expression()
{
    // если тип текущего токена не равен (
    if (_lex->current_token_type() != token_type::LPAR)
    {
        // то возбуждаем ошибку "Ожидалась '('"
        error("'(' expected");
    }
    // если ошибки нет, то сдвигаем текущий токен
    _lex->next_token();

    // вызываем метод expression, согласно грамматике
    Node* exression_node = additive_expression();

    // если тип текущего токена не равен )
    if (_lex->current_token_type() != token_type::RPAR)
    {
        // то возбуждаем ошибку "Ожидалась ')'"
        error("')' expected");
    }
    // если ошибки нет, то сдвигаем текущий токен
    _lex->next_token();

    return exression_node; // по-умолчанию возвращаем nullptr
}

Node* Parser::number()
{
    // если тип текущего токена не число
    if (_lex->current_token_type() != token_type::NUMBER)
    {
        // то возбуждаем ошибку "Ожидалось число!"
        error("Number expected!");
    }
    // если же это число то
    // получаем значение текущего токена, которое равно числу
    string number_str = (_lex->current_token()).Get_Lexem();

    // сдвигаем текущий токен
    _lex->next_token();

    // создаем новый узел с типом CONSTANT и значением равным значению
    // из лексемы текущего токена
    Node* number_node = new Node(Node_type::CONSTANT, number_str);
    // возвращаем полученный узел
    return number_node;
}

Node* Parser::variable() 
{
    if (_lex->current_token_type() != token_type::VARIABLE)
    {
        // то возбуждаем ошибку "Ожидалось число!"
        error("Variable expected!");
    }
    string variable_str = (_lex->current_token()).Get_Lexem();
    _lex->next_token();
    Node* variable_node;
    if (table.has_variable(variable_str))
    {
        Variable* var = table.get_variable_by_name(variable_str);
        if (var->Is_Const())
            variable_node = new Node(Node_type::USING_CONSTANT_VARIABLE, variable_str);
        else
            variable_node = new Node(Node_type::USING_VARIABLE, variable_str);
    }
    else
    {
        variable_node = new Node(Node_type::VARIABLE, variable_str);
    }
    return variable_node;
}

Node* Parser::ifstatement()
{
    _lex->next_token();

    Node* condition_node = condition();
    Node* expression_node = noteblock();
    Node* temp = new Node(Node_type::IF, "");
    temp->rNode.push_back(condition_node);
    temp->rNode.push_back(expression_node);
    if (_lex->current_token_type() == token_type::ELSE)
    {
        _lex->next_token();
        Node* elsenode = new Node(Node_type::ELSE, "");
        if (_lex->current_token_type() == token_type::IF)
        {
            Node* iftemp = ifstatement();
            elsenode->rNode.push_back(iftemp);
        }
        else
        {
            Node* iftemp = noteblock();
            elsenode->rNode.push_back(iftemp);
        }
        temp->rNode.push_back(elsenode);
        
    }
    return temp;
}

Node* Parser::range()
{
    Node* temp = primary_expression();
    if (_lex->current_token_type() != token_type::DOTS)
    {
        throw runtime_error("Expected '...'");
    }
    _lex->next_token();
    Node* primary = primary_expression();
    Node* range = new Node(Node_type::IN, "");
    range->rNode.push_back(temp);
    range->rNode.push_back(primary);
    return range;
}

Node* Parser::print()
{
    if (_lex->current_token_type() != token_type::LPAR)
    {
        throw runtime_error("Expected '('");
    }
    _lex->next_token();
    Node* value = additive_expression();
    if (_lex->current_token_type() != token_type::RPAR)
    {
        throw runtime_error("Expected ')'");
    }
    _lex->next_token();
    Node* print = new Node(Node_type::PRINT, "");
    print->rNode.push_back(value);
    return print;
}
