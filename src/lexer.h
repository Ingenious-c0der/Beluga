#ifndef LEXER_H
#define LEXER_H
#include<iostream> 
#include "token.h"
class LEXER_Element
{
public:
    std::string value;
    Token type;
    LEXER_Element(std::string value, Token type)
    {
        this->value = value;
        this->type = type;
    }
    LEXER_Element()
    {
        this->value = "";
        this->type = Token::UNKNOWN_SYMBOL_TOKEN;
    }
};

#endif