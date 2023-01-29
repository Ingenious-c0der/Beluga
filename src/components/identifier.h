#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#include <vector>
#include "../lexer.h"

// static class for delivering the identifier method
class Identifier
{

public:
    static void identify(std::vector<LEXER_Element> &);
};
// this function is optimistic while assuming grammar while identifying, wrong grammar may pass this stage but will not pass in verifier
// passing one machine at a time is encouraged for component checks to work properly
void Identifier::identify(std::vector<LEXER_Element> &unid_elements)
{

    try
    {
        for (int i = 0; i < unid_elements.size(); i++)
        {
            if (unid_elements[i].type == Token::CPL_TOKEN || unid_elements[i].type == Token::CPR_TOKEN || unid_elements[i].type == Token::CBL_TOKEN || unid_elements[i].type == Token::CBR_TOKEN || unid_elements[i].type == Token::FAT_ARROW_TOKEN)
            {
                continue;
            }
            else if (unid_elements[i].type == Token::MACHINE_TOKEN)
            {
                if (unid_elements[i + 1].type == Token::CPL_TOKEN && unid_elements[i + 2].type == Token::UNKNOWN_CONDENSED_TOKEN && unid_elements[i + 3].type == Token::CPR_TOKEN)
                {
                    unid_elements[i + 2].type = Token::MACHINE_NAME_TOKEN;
                    i += 3;
                }
                else
                {
                    // throw error
                    throw ERROR_TYPES::INVALID_MACHINE_DEFINITION;
                }
            }
            else if (unid_elements[i].type == Token::CONSUMES_TOKEN)
            {
                i += 2;
                while (unid_elements[i].type != Token::CPR_TOKEN)
                {
                    if (unid_elements[i].type == Token::UNKNOWN_CONDENSED_TOKEN)
                    {
                        unid_elements[i].type = Token::EXTERNAL_TURING_MACHINE_NAME_TOKEN;
                    }
                    i++;
                }
            }
            else if (unid_elements[i].type == Token::TAPE_TOKEN)
            {
                i += 2;
                while (unid_elements[i].type != Token::CPR_TOKEN)
                {
                    if (unid_elements[i].type == Token::UNKNOWN_CONDENSED_TOKEN && unid_elements[i - 1].type == Token::CBL_TOKEN && unid_elements[i + 1].type == Token::COMMA_TOKEN)
                    {
                        unid_elements[i].type = Token::TAPE_NAME_TOKEN;
                    }
                    else if (unid_elements[i].type == Token::UNKNOWN_CONDENSED_TOKEN && unid_elements[i - 1].type == Token::COMMA_TOKEN && unid_elements[i + 1].type == Token::CBR_TOKEN)
                    {
                        unid_elements[i].type = Token::TAPE_CONTENTS_TOKEN;
                    }
                    i++;
                }
            }
            else if (unid_elements[i].type == Token::DEF_TOKEN)
            {
                i += 3;
                // Q_SET
                while (unid_elements[i].type != Token::CBR_TOKEN)
                {
                    if (unid_elements[i].type == Token::UNKNOWN_CONDENSED_TOKEN)
                    {
                        unid_elements[i].type = Token::STATE_TOKEN;
                    }
                    i++;
                }
                i++;
                // SIGMA_SET
                while (unid_elements[i].type != Token::CBR_TOKEN)
                {
                    if (unid_elements[i].type == Token::UNKNOWN_CONDENSED_TOKEN)
                    {
                        unid_elements[i].type = Token::INPUT_SYMBOL_TOKEN;
                    }
                    i++;
                }
                i += 2;
                // TRANSITION_SET
                while (unid_elements[i].type != Token::CBR_TOKEN)
                {
                    if (unid_elements[i].type == Token::CPL_TOKEN)
                    {
                        unid_elements[i + 1].type = Token::STATE_TOKEN;
                        unid_elements[i + 3].type = Token::READ_SYMBOL_TOKEN;
                        unid_elements[i + 5].type = Token::STATE_TOKEN;
                        unid_elements[i + 7].type = Token::WRITE_SYMBOL_TOKEN;
                        unid_elements[i + 9].type = Token::TRANSITION_DIRECTION_TOKEN;
                        unid_elements[i + 11].type = Token::TAPE_NAME_TOKEN;
                        unid_elements[i + 13].type = Token::TAPE_NAME_TOKEN;
                        if (unid_elements[i + 14].type == Token::CPR_TOKEN)
                        {
                            i += 15;
                        }
                        else
                        {
                            std::cout << i << " " << unid_elements[i].value << " " << tokenToString(unid_elements[i].type) << std::endl;
                            throw ERROR_TYPES::INVALID_TRANSITION_DEFINITION;
                        }
                    }
                    else if (unid_elements[i].type == Token::COMMA_TOKEN)
                    {
                        i++;
                        continue;
                    }
                    else
                    {
                        std::cout << i << " " << unid_elements[i].value << " " << tokenToString(unid_elements[i].type) << std::endl;
                        throw ERROR_TYPES::INVALID_TRANSITION_DEFINITION;
                    }
                }
                i++;
                // INTIAL_STATE
                if (unid_elements[i].type == Token::CPL_TOKEN && unid_elements[i + 1].type == Token::UNKNOWN_CONDENSED_TOKEN && unid_elements[i + 2].type == Token::CPR_TOKEN)
                {
                    unid_elements[i + 1].type = Token::INITIAL_STATE_TOKEN;
                }
                i += 3;
                // BLANK_SYMBOL
                if (unid_elements[i].type == Token::CPL_TOKEN && unid_elements[i + 1].type == Token::UNKNOWN_CONDENSED_TOKEN && unid_elements[i + 2].type == Token::CPR_TOKEN)
                {
                    unid_elements[i + 1].type = Token::BLANK_SYMBOL_TOKEN;
                }
                i += 3;
                // FINAL_STATES
                if (unid_elements[i].type == Token::CPL_TOKEN)
                {
                    while (unid_elements[i].type != Token::CPR_TOKEN)
                    {
                        if (unid_elements[i].type == Token::UNKNOWN_CONDENSED_TOKEN)
                        {
                            unid_elements[i].type = Token::FINAL_STATE_TOKEN;
                        }
                        i++;
                    }
                }
            }
            else if (unid_elements[i].type == Token::IGNORE_UNKNOWNS_TOKEN)
            {
                i += 2;
                if (unid_elements[i].type == Token::CPL_TOKEN && unid_elements[i + 1].type == Token::ACCEPT_TOKEN || unid_elements[i + 1].type == Token::REJECT_TOKEN && unid_elements[i + 2].type == Token::CPR_TOKEN)
                {
                    unid_elements[i + 1].type = Token::DECISION_TOKEN;
                }
                i += 2;
            }
            else if (unid_elements[i].type == Token::RELAY_TOKEN)
            {

                i += 3;
                if (unid_elements[i].type == Token::ON_ACCEPT_TOKEN)
                {
                    i += 2;
                    while (unid_elements[i].type != Token::CPR_TOKEN)
                    {
                        if (unid_elements[i].type == Token::UNKNOWN_CONDENSED_TOKEN)
                        {
                            unid_elements[i].type = Token::EXTERNAL_TURING_MACHINE_NAME_TOKEN;
                        }
                        i++;
                    }
                    i++;
                }
                if (unid_elements[i].type == Token::ON_REJECT_TOKEN)
                {
                    i += 2;
                    while (unid_elements[i].type != Token::CPR_TOKEN)
                    {
                        if (unid_elements[i].type == Token::UNKNOWN_CONDENSED_TOKEN)
                        {
                            unid_elements[i].type = Token::EXTERNAL_TURING_MACHINE_NAME_TOKEN;
                        }
                        i++;
                    }
                    i++;
                }
                i++;
            }
        }
        std::vector<int> component_marking = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        // checking if all the basic components are present which cannot be left empty
        for (auto token : unid_elements)
        {

            switch (token.type)
            {
            case Token::CONSUMES_TOKEN:
                component_marking[0] = 1;
                break;
            case Token::TAPE_TOKEN:
                component_marking[1] = 1;
                break;
            case Token::DEF_TOKEN:
                component_marking[2] = 1;
                break;
            case Token::IGNORE_UNKNOWNS_TOKEN:
                component_marking[3] = 1;
                break;
            case Token::RELAY_TOKEN:
                component_marking[4] = 1;
                break;
            case Token::ON_ACCEPT_TOKEN:
                component_marking[5] = 1;
                break;
            case Token::ON_REJECT_TOKEN:
                component_marking[6] = 1;
                break;
            case Token::INITIAL_STATE_TOKEN:
                component_marking[7] = 1;
                break;
            case Token::FINAL_STATE_TOKEN:
                component_marking[8] = 1;
                break;
            case Token::BLANK_SYMBOL_TOKEN:
                component_marking[9] = 1;
                break;
            case Token::DECISION_TOKEN:
                component_marking[10] = 1;
                break;
            case Token::INPUT_SYMBOL_TOKEN:
                component_marking[11] = 1;
                break;
            case Token::STATE_TOKEN:
                component_marking[12] = 1;
                break;
            case Token::UNKNOWN_CONDENSED_TOKEN:
                throw ERROR_TYPES::UNKNOWN_TOKEN_FOUND;
                break;
            }
        }
        for (auto i : component_marking)
        {
            if (i == 0)
            {
                throw ERROR_TYPES::MISSING_COMPONENT;
            }
        }
    }
    catch (ERROR_TYPES &e)
    {
        std::cout << stringify(e) << std::endl;
        exit(1);
    }
}

#endif