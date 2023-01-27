#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "lexer.h"


std::vector<LEXER_Element> lex(std::string filename)
{

    std::ifstream file(filename);
    std::string line;
    std::vector<LEXER_Element> tokens;
    while (std::getline(file, line))
    {

        for (int i = 0; i < line.length(); i++)
        {
            char c = line[i];
            if (c == '{')
            {
                tokens.push_back(LEXER_Element("{", Token::CBL_TOKEN));
            }
            else if (c == '}')
            {
                tokens.push_back(LEXER_Element("}", Token::CBR_TOKEN));
            }
            else if (c == '(')
            {
                tokens.push_back(LEXER_Element("(", Token::CPL_TOKEN));
            }
            else if (c == ')')
            {
                tokens.push_back(LEXER_Element(")", Token::CPR_TOKEN));
            }
            else if (c == '/')
            {
                tokens.push_back(LEXER_Element("/", Token::FORWARD_SLASH_TOKEN));
            }
            else if (c == ',')
            {
                tokens.push_back(LEXER_Element(",", Token::COMMA_TOKEN));
            }
            else if (c == '-')
            {
                tokens.push_back(LEXER_Element("-", Token::DASH_TOKEN));
            }
            else if (c == '>')
            {
                tokens.push_back(LEXER_Element(">", Token::TRANSITION_DIRECTION_RIGHT_TOKEN));
            }
            else if (c == '<')
            {
                tokens.push_back(LEXER_Element("<", Token::TRANSITION_DIRECTION_LEFT_TOKEN));
            }
            else if (c == '=')
            {
                if (line[i + 1] == '>')
                {
                    tokens.push_back(LEXER_Element("=>", Token::FAT_ARROW_TOKEN));
                    i++;
                }
            }
            else if(c == '*')
            {
                tokens.push_back(LEXER_Element("*", Token::ASTERISK_TOKEN));
            }
            else if (c == ' ')
            {
                continue;
            }
            else if(c == ':' )
            {
                tokens.push_back(LEXER_Element(":", Token::COLON_TOKEN));
            }
            else
            {
                tokens.push_back(LEXER_Element(std::string(1, c), Token::UNKNOWN_SYMBOL_TOKEN));
            }
        }
    }
    // for (int i = 0; i < tokens.size(); i++)
    // {
    //     std::cout << tokens[i].value << " is "<<tokenToString(tokens[i].type)<<std::endl;
    // }
    
    return tokens;
}