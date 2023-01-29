#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#include <vector>
#include "lexer.h"

// static class for delivering the identifier method
class Identifier
{

public:
    static std::vector<LEXER_Element> identify(std::vector<LEXER_Element> elements);
};



std::vector<LEXER_Element>Identifier:: identify(std::vector<LEXER_Element> unid_tokens)
{
    for(int i = 0 ; i< unid_tokens.size(); i++)
    {
        
    }
}





#endif