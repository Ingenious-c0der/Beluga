#ifndef SYMBOL_H
#define SYMBOL_H
#include <iostream>
#include "types.h"

class Symbol
{

    std::string name;
    Subtype subtype;

public:
    Symbol(); // default constructor
    Symbol(std::string, Subtype);
};

Symbol::Symbol()
{
    this->name = "symbol_undefined";
    this->subtype = Subtype::UNDEFINED;
}

Symbol::Symbol(std::string name, Subtype subtype)
{
    this->name = name;
    this->subtype = subtype;
}

#endif;
