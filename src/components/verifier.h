#ifndef VERIFIER_H
#define VERIFIER_H
#include "../lexer.h"
#include <vector>

static const std::vector<Token> MACHINE_DEF_GRAMMAR = {Token::MACHINE_TOKEN, Token::CPL_TOKEN, Token::MACHINE_NAME_TOKEN, Token::CPR_TOKEN, Token::FAT_ARROW_TOKEN, Token::CBL_TOKEN};
static const std::vector<Token> TAPE_DEF_GRAMMAR = {Token::TAPE_TOKEN, Token::COLON_TOKEN, Token::CPL_TOKEN, Token::TAPE_PUMPING_TOKEN, Token::CPR_TOKEN};
static const std::vector<Token> TAPE_UNIT_DEF_GRAMMAR = {Token::CBL_TOKEN, Token::TAPE_NAME_TOKEN, Token::COMMA_TOKEN, Token::TAPE_CONTENTS_TOKEN, Token::CBR_TOKEN};
static const std::vector<Token> TRANSITION_UNIT_DEF_GRAMMAR = {Token::CPL_TOKEN, Token::STATE_TOKEN, Token::COMMA_TOKEN, Token::READ_SYMBOL_TOKEN, Token::COMMA_TOKEN, Token::WRITE_SYMBOL_TOKEN, Token::COMMA_TOKEN, Token::TRANSITION_DIRECTION_TOKEN, Token::COMMA_TOKEN, Token::TAPE_NAME_TOKEN, Token::TAPE_CONTENTS_TOKEN, Token::CPR_TOKEN};
static const std::vector<Token> TRANSITION_DEF_GRAMMAR = {Token::CBL_TOKEN, Token::TRANSITION_PUMPING_TOKEN, Token::CBR_TOKEN};
static const std::vector<Token> Q_SET_DEF_GRAMMAR = {Token::CBL_TOKEN, Token::Q_SET_PUMPING_TOKEN, Token::CBR_TOKEN};
static const std::vector<Token> SIGMA_SET_DEF_GRAMMAR = {Token::CBL_TOKEN, Token::SIGMA_SET_PUMPING_TOKEN, Token::CBR_TOKEN};
static const std::vector<Token> INTIAL_STATE_DEF_GRAMMAR = {Token::CPL_TOKEN, Token::INITIAL_STATE_TOKEN, Token::CPR_TOKEN};
static const std::vector<Token> BLANK_SYMBOL_DEF_GRAMMAR = {Token::CPL_TOKEN, Token::BLANK_SYMBOL_TOKEN, Token::CPR_TOKEN};
static const std::vector<Token> FINAL_STATE_DEF_GRAMMAR = {Token::CPL_TOKEN, Token::FINAL_STATE_PUMPING_TOKEN, Token::CPR_TOKEN};
static const std::vector<Token> IGNORE_UNKNOWNS_DEF_GRAMMAR = {Token::IGNORE_UNKNOWNS_TOKEN, Token::COLON_TOKEN, Token::CPL_TOKEN, Token::DECISION_TOKEN, Token::CPR_TOKEN};
static const std::vector<Token> RELAY_DEF_GRAMMAR = {Token::RELAY_TOKEN, Token::COLON_TOKEN, Token::CBL_TOKEN, Token::ON_ACCEPT_TOKEN, Token::COLON_TOKEN, Token::CPL_TOKEN, Token::RELAY_ACCEPT_PUMPING_TOKEN, Token::CPR_TOKEN, Token::ON_REJECT_TOKEN, Token::COLON_TOKEN, Token::CPL_TOKEN, Token::RELAY_REJECT_PUMPING_TOKEN, Token::CPR_TOKEN, Token::CBR_TOKEN};
static const std::vector<Token> MACHINE_CONTENTS_GRAMMAR = {Token::CBL_TOKEN, Token::CONSUMES_TOKEN, Token::TAPE_TOKEN, Token::DEF_TOKEN, Token::IGNORE_UNKNOWNS_TOKEN, Token::RELAY_TOKEN, Token::CBR_TOKEN};
static const std::vector<Token> CONSUMES_DEF_GRAMMAR = {Token::CONSUMES_TOKEN, Token::COLON_TOKEN, Token::CPL_TOKEN, Token::CONSUMES_PUMPING_TOKEN, Token::CPR_TOKEN};
static const std::vector<Token> DEF_DEF_GRAMMAR = {Token::DEF_TOKEN, Token::COLON_TOKEN, Token::CPL_TOKEN, Token::Q_SET_DEF_TOKEN, Token::SIGMA_DEF_TOKEN, Token::TRANSITION_DEF_TOKEN, Token::INITIAL_STATE_DEF_TOKEN, Token::BLANK_SYMBOL_DEF_TOKEN, Token::FINAL_STATE_DEF_TOKEN, Token::CPR_TOKEN};
//@semantic class, holds grammar for particular types
class Verifier
{

    // consider comma tokens in pumping tokens

public:
    Verifier();
    static bool verify_grammar(std::vector<Token>, Grammar_Type);
};

Verifier::Verifier(){};
bool Verifier::verify_grammar(std::vector<Token> tokens, Grammar_Type GT)
{
    if (GT == Grammar_Type::MACHINE_DEF_GRAMMAR)
    {
        for (int i = 0; i < tokens.size(); i++)
        {
            if (tokens[i] != MACHINE_DEF_GRAMMAR[i])
            {
                return false;
            }
        }
        return true;
    }
    else if (GT == Grammar_Type::CONSUMES_DEF_GRAMMAR)
    {
        int i = 0;
        while (CONSUMES_DEF_GRAMMAR[i] != Token::CONSUMES_PUMPING_TOKEN)
        {
            if (tokens[i] != CONSUMES_DEF_GRAMMAR[i])
            {
                return false;
            }
            i++;
        }

        while (tokens[i] != Token::CPR_TOKEN)
        {
            if (tokens[i] == Token::COMMA_TOKEN && (tokens[i + 1] == Token::EXTERNAL_TURING_MACHINE_NAME_TOKEN || tokens[i + 1] == Token::NULL_TOKEN))
            {
                i++;
            }
            else if (tokens[i] == Token::EXTERNAL_TURING_MACHINE_NAME_TOKEN || tokens[i] == Token::NULL_TOKEN)
            {
                i++;
            }
            else
            {
                return false;
            }
        }
        std::cout << "CHECK : " << tokens.size() - 1 << " with " << i << std::endl;
        if (tokens[i] == Token::CPR_TOKEN && tokens.size() - 1 == i)
        {
            return true;
        }
        return false;
    }
    else if (GT == Grammar_Type::TAPE_DEF_GRAMMAR)
    {
        int i = 0;
        while (TAPE_DEF_GRAMMAR[i] != Token::TAPE_PUMPING_TOKEN)
        {
            if (tokens[i] != TAPE_DEF_GRAMMAR[i])
            {
                return false;
            }
            i++;
        }
        int j = 0;
        std::cout << tokens.size() << std::endl;
        while (tokens[i] != Token::CPR_TOKEN)
        {

            if (tokens[i] != TAPE_UNIT_DEF_GRAMMAR[j])
            {

                return false;
            }
            if (j == TAPE_UNIT_DEF_GRAMMAR.size() - 1)
            {
                // std::cout<< "j = " << j << tokenToString(TAPE_UNIT_DEF_GRAMMAR[j])<< std::endl;
                // std::cout<< "i = " << i << tokenToString(tokens[i])<< std::endl;
                j = 0;
                if (tokens[i + 1] == Token::COMMA_TOKEN)
                    i++;
            }
            else
            {
                j++;
            }
            i++;
        }
        std::cout << "CHECK : " << tokens.size() - 1 << " with " << i << std::endl;
        if (tokens[i] == Token::CPR_TOKEN && i == tokens.size() - 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else if (GT == Grammar_Type::DEF_DEF_GRAMMAR)
    {
        int i = 0;
        while (tokens[i] != Token::Q_SET_DEF_TOKEN)
        {
            if (tokens[i] != TRANSITION_DEF_GRAMMAR[i])
            {
                return false;
            }
            i++;
        }
        // matching grammar for Q set

        while (tokens[i] != Token::CBR_TOKEN)
        {
            if (tokens[i] == Token::COMMA_TOKEN && tokens[i + 1] == Token::STATE_TOKEN)
            {
                i++;
            }
            else if (tokens[i] == Token::STATE_TOKEN && tokens[i - 1] == Token::COMMA_TOKEN)
            {
                i++;
            }
            else
            {
                return false;
            }
        }
        if (tokens[i] != Token::CBR_TOKEN)
        {
            return false;
        }
        i++;
        // for matching sigma set
        if (tokens[i] != Token::CBL_TOKEN)
        {
            return false;
        }
        while (tokens[i] != Token::CBR_TOKEN)
        {
            if (tokens[i] == Token::COMMA_TOKEN && tokens[i + 1] == Token::INPUT_SYMBOL_TOKEN)
            {
                i++;
            }
            else if (tokens[i] == Token::INPUT_SYMBOL_TOKEN && tokens[i - 1] == Token::COMMA_TOKEN)
            {
                i++;
            }
            else
            {
                return false;
            }
        }
        if (tokens[i] != Token::CBR_TOKEN)
        {
            return false;
        }
        i++;
        std::cout << "TESTING TILL HERE COMPLETE" << std::endl;
        // for matching transition set
        if (tokens[i] != Token::CBL_TOKEN)
        {
            return false;
        }
        for (int k = 0; k < TRANSITION_DEF_GRAMMAR.size(); k++)
        {

            if (tokens[i] == Token::TRANSITION_PUMPING_TOKEN)
            {
                int j = 0;
                int store = 0;
                for (int m = i; m < tokens.size(); m++)
                {
                    if (tokens[m] == TRANSITION_UNIT_DEF_GRAMMAR[j])
                    {
                        j++;
                        store = m;
                    }
                    if (TRANSITION_UNIT_DEF_GRAMMAR[j] == Token::CPR_TOKEN)
                    {
                        j = 0;
                    }
                    else
                    {
                        return false;
                    }
                }
                i++;
            }

            else if (tokens[i] != TRANSITION_DEF_GRAMMAR[k])
            {
                return false;
            }
            if (tokens[i] == Token::CPR_TOKEN)
            {
                break;
            }
            i++;
        }
        i++;
        // remaining 3 entities

        if (tokens[i] == Token::CPL_TOKEN && tokens[i + 1] == Token::STATE_TOKEN && tokens[i + 2] == Token::CPR_TOKEN)
        {
            i += 3;
        }
        else
        {
            return false;
        }
        if (tokens[i] == Token::CPL_TOKEN && tokens[i + 1] == Token::BLANK_SYMBOL_TOKEN && tokens[i + 2] == Token::CPR_TOKEN)
        {
            i += 3;
        }
        else
        {
            return false;
        }
        if (tokens[i] == Token::CPL_TOKEN && tokens[i + 1] == Token::STATE_TOKEN && tokens[i + 2] == Token::CPR_TOKEN)
        {
            i += 3;
        }
        else
        {
            return false;
        }

        if (tokens[i] == Token::CPR_TOKEN)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else if (GT == Grammar_Type::IGNORE_UNKNOWNS_DEF_GRAMMAR)
    {
        int h = 0;
        for (int i = 0; i < tokens.size(); i++)
        {
            if (tokens[i] == IGNORE_UNKNOWNS_DEF_GRAMMAR[h])

            {
                h++;
            }
            else
            {
                return false;
            }
        }
        if (tokens[h] == Token::CPR_TOKEN && h == tokens.size() - 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else if (GT == Grammar_Type::RELAY_DEF_GRAMMAR)
    {

        for (int j = 0; j < RELAY_DEF_GRAMMAR.size(); j++)
        {

            if (RELAY_DEF_GRAMMAR[j] == Token::RELAY_ACCEPT_PUMPING_TOKEN)
            {

                while (tokens[j] != Token::CPR_TOKEN)
                {
                    if (tokens[j] == Token::EXTERNAL_TURING_MACHINE_NAME_TOKEN || tokens[j] == Token::CONSOLE_TOKEN || tokens[j] == Token::NULL_TOKEN)
                    {
                        j++;
                    }
                    else if (tokens[j] == Token::COMMA_TOKEN && (tokens[j - 1] == Token::EXTERNAL_TURING_MACHINE_NAME_TOKEN || tokens[j - 1] == Token::NULL_TOKEN))
                    {
                        j++;
                    }
                    else
                    {
                        return false;
                    }
                }
                j++;
                if (tokens[j] == Token::ON_REJECT_TOKEN && tokens[j + 1] == Token::COLON_TOKEN && tokens[j + 2] == Token::CPL_TOKEN)
                {
                    j += 3;
                    while (tokens[j] != Token::CPR_TOKEN)
                    {
                        if (tokens[j] == Token::EXTERNAL_TURING_MACHINE_NAME_TOKEN || tokens[j] == Token::CONSOLE_TOKEN || tokens[j] == Token::NULL_TOKEN)
                        {
                            j++;
                        }
                        else if (tokens[j] == Token::COMMA_TOKEN && (tokens[j - 1] == Token::EXTERNAL_TURING_MACHINE_NAME_TOKEN || tokens[j - 1] == Token::NULL_TOKEN))
                        {
                            j++;
                        }
                        else
                        {
                            return false;
                        }
                    }
                }
            }
            else if (tokens[j] == RELAY_DEF_GRAMMAR[j])
            {
                continue;
            }
            else
            {
                return false;
            }
        }
    }
    else
    {
        return false;
    }
}

#endif