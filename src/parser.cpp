#include <iostream>
#include <stack>
#include <queue>
#include "machine.h"
#include <vector>
#include <cstring>
#include <iostream>
#include "parser.h"
#include "types.h"
#include "lexer.cpp"
#include "components/identifier.h"
#include <stack>

// std::vector<Machine> parse(std::vector<LEXER_Element> tokens)
// {

//     std::vector<Machine> GENERATED_machines;
//     for (auto token : tokens)
//     {
//     }
// }

// token condensation
std::vector<LEXER_Element> condensor(std::vector<LEXER_Element> tokens)
{
    std::vector<LEXER_Element> condensed_tokens;
    for (int i = 0; i < tokens.size(); i++)
    {
        if (tokens[i].type == Token::UNKNOWN_SYMBOL_TOKEN)
        {
            std::string condensed_value = "";
            while (tokens[i].type == Token::UNKNOWN_SYMBOL_TOKEN)
            {
                condensed_value += tokens[i].value;
                i++;
            }
            i--;
            condensed_tokens.push_back(LEXER_Element(condensed_value, Token::UNKNOWN_CONDENSED_TOKEN));
        }
        else
        {
            condensed_tokens.push_back(tokens[i]);
        }
    }
    // for (auto token : condensed_tokens)
    // {
    //     std::cout << token.value << " - " << tokenToString(token.type) << std::endl;
    // }
    // std::cout<<"*********************"<<std::endl;

    return condensed_tokens;
}

// primary identification and classification on condensed tokens before machine tree building
// comments removal
std::vector<LEXER_Element> sanitizer_primary(std::vector<LEXER_Element> unclean_tokens)
{
    std::vector<LEXER_Element> san_primary_tokens;
    for (int i = 0; i < unclean_tokens.size(); i++)
    {
        if (unclean_tokens[i].type == Token::UNKNOWN_CONDENSED_TOKEN)
        {
            if (unclean_tokens[i].value == "machine")
            {
                san_primary_tokens.push_back(LEXER_Element(unclean_tokens[i].value, Token::MACHINE_TOKEN));
            }
            else if (unclean_tokens[i].value == "consumes")
            {
                san_primary_tokens.push_back(LEXER_Element(unclean_tokens[i].value, Token::CONSUMES_TOKEN));
            }
            else if (unclean_tokens[i].value == "tape")
            {
                san_primary_tokens.push_back(LEXER_Element(unclean_tokens[i].value, Token::TAPE_TOKEN));
            }
            else if (unclean_tokens[i].value == "relay")
            {
                san_primary_tokens.push_back(LEXER_Element(unclean_tokens[i].value, Token::RELAY_TOKEN));
            }
            else if (unclean_tokens[i].value == "def")
            {
                san_primary_tokens.push_back(LEXER_Element(unclean_tokens[i].value, Token::DEF_TOKEN));
            }
            else if (unclean_tokens[i].value == "ignoreUnknowns")
            {
                san_primary_tokens.push_back(LEXER_Element(unclean_tokens[i].value, Token::IGNORE_UNKNOWNS_TOKEN));
            }
            else if (unclean_tokens[i].value == "onAccept")
            {
                san_primary_tokens.push_back(LEXER_Element(unclean_tokens[i].value, Token::ON_ACCEPT_TOKEN));
            }
            else if (unclean_tokens[i].value == "onReject")
            {
                san_primary_tokens.push_back(LEXER_Element(unclean_tokens[i].value, Token::ON_REJECT_TOKEN));
            }
            else if (unclean_tokens[i].value == "accept")
            {
                san_primary_tokens.push_back(LEXER_Element(unclean_tokens[i].value, Token::ACCEPT_TOKEN));
            }
            else if (unclean_tokens[i].value == "reject")
            {
                san_primary_tokens.push_back(LEXER_Element(unclean_tokens[i].value, Token::REJECT_TOKEN));
            }
            else if (unclean_tokens[i].value == "null")
            {
                san_primary_tokens.push_back(LEXER_Element(unclean_tokens[i].value, Token::NULL_TOKEN));
            }
            else if (unclean_tokens[i].value == "console")
            {
                san_primary_tokens.push_back(LEXER_Element(unclean_tokens[i].value, Token::CONSOLE_TOKEN));
            }
            else
            {
                san_primary_tokens.push_back(unclean_tokens[i]);
            }
        }
        else if (unclean_tokens[i].type == Token::DASH_TOKEN)
        {
            if (unclean_tokens[i + 1].type == Token::TRANSITION_DIRECTION_RIGHT_TOKEN)
            {
                san_primary_tokens.push_back(LEXER_Element("->", Token::ARROW_RIGHT_TOKEN));
                i++; // skip the next token
            }
            else if (unclean_tokens[i - 1].type == Token::TRANSITION_DIRECTION_LEFT_TOKEN)
            {
                san_primary_tokens.pop_back(); // remove the previous token
                san_primary_tokens.push_back(LEXER_Element("<-", Token::ARROW_LEFT_TOKEN));
            }
        }
        else if (unclean_tokens[i].type == Token::FORWARD_SLASH_TOKEN)
        {
            if (unclean_tokens[i + 1].type == Token::ASTERISK_TOKEN)
            {
                i += 2; // skip the next token
                bool flag = true;
                while (flag)
                {
                    if (unclean_tokens[i].type == Token::ASTERISK_TOKEN)
                    {
                        if (unclean_tokens[i + 1].type == Token::FORWARD_SLASH_TOKEN)
                        {
                            flag = false;
                        }
                    }
                    i++; // skip the next token
                }
            }
        }
        else
        {
            san_primary_tokens.push_back(unclean_tokens[i]);
        }
    }


    return san_primary_tokens;
}

// unknown token classification based on the positions and grammar of the language
std::vector<LEXER_Element> sanitizer_secondary(std::vector<LEXER_Element> partial_unknown_tokens)
{
    // parenthesis matching and checks
    std::stack<LEXER_Element> parenthesis_stack;
    //the error location detection is quite garbage as of now 

    try
    {
        for (int i = 0; i < partial_unknown_tokens.size(); i++)
        {
            if (partial_unknown_tokens[i].type == Token::CPL_TOKEN)
            {
                parenthesis_stack.push(partial_unknown_tokens[i]);
            }
            else if (partial_unknown_tokens[i].type == Token::CPR_TOKEN)
            {
                if (parenthesis_stack.top().type == Token::CPL_TOKEN)
                {
                    parenthesis_stack.pop();
                }
                else
                {
                    throw std::runtime_error("Syntax Error : Mismatched Parenthesis , No opening bracket found for  " + partial_unknown_tokens[i - 1].value + " >> ) <<  " + ( i+1 > partial_unknown_tokens.size() - 1 ?"END": partial_unknown_tokens[i + 1].value));
                }
            }
            else if (partial_unknown_tokens[i].type == Token::CBL_TOKEN)
            {
                parenthesis_stack.push(partial_unknown_tokens[i]);
              
            }
            else if (partial_unknown_tokens[i].type == Token::CBR_TOKEN)
            {
                if (parenthesis_stack.top().type == Token::CBL_TOKEN)
                {
                    parenthesis_stack.pop();
                }
                else
                {
                    throw std::runtime_error("Syntax Error : Mismatched Parenthesis , No opening bracket found for " + partial_unknown_tokens[i - 1].value + " >> } << " + (i+1 > partial_unknown_tokens.size() - 1?" END ": partial_unknown_tokens[i + 1].value));
                }
            }
        }

        if (!parenthesis_stack.empty())
        {
           
            std::string error_top = parenthesis_stack.top().value;
            throw std::runtime_error("Syntax Error : Missing Appropriate Parenthesis for " + error_top + " at the end of the file");
        }
        else
        {
            std::cout << "Brackets match test passed" << std::endl;
        }

        Identifier().identify(partial_unknown_tokens) ;
        auto known_tokens = partial_unknown_tokens ;
        // cout known tokens 
        for (auto token : known_tokens)
        {
            std::cout << token.value << " - " << tokenToString(token.type) << std::endl;
        }




    }
    catch (std::runtime_error e)
    {
      
        std::cout << e.what() << std::endl;
        exit(1);
    }
    //cout tokens ; 
    

    return partial_unknown_tokens;
}

// checks if all the components required to build each machine are present : last stage before machine building is done in main
//  parser function
// std::vector<LEXER_Element> sanitizer_tertiary(std::vector<LEXER_Element> ordered_known_tokens)
// {
//     // todo
// }

// testing
int main()
{
    auto x = lex("../examples/first.beluga");
    auto y = condensor(x);
    auto z = sanitizer_primary(y);
    sanitizer_secondary(z);
}