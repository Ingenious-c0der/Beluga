#include <iostream>
#include <stack>
#include <queue>
#include "components/machine.h"
#include <vector>
#include <cstring>
#include <iostream>
#include "parser.h"
#include "types.h"
#include "components/verifier.h"
#include "lexer.cpp"
#include "components/identifier.h"
#include <stack>

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
            else if(unclean_tokens[i].value == "import")
            {
                san_primary_tokens.push_back(LEXER_Element(unclean_tokens[i].value, Token::IMPORT_TOKEN));
            }
            else if(unclean_tokens[i].value == "from")
            {
                san_primary_tokens.push_back(LEXER_Element(unclean_tokens[i].value, Token::IMPORT_FROM_TOKEN));
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
    // the error location detection is quite garbage as of now

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
                    throw std::runtime_error("Syntax Error : Mismatched Parenthesis , No opening bracket found for  " + partial_unknown_tokens[i - 1].value + " >> ) <<  " + (i + 1 > partial_unknown_tokens.size() - 1 ? "END" : partial_unknown_tokens[i + 1].value));
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
                    throw std::runtime_error("Syntax Error : Mismatched Parenthesis , No opening bracket found for " + partial_unknown_tokens[i - 1].value + " >> } << " + (i + 1 > partial_unknown_tokens.size() - 1 ? " END " : partial_unknown_tokens[i + 1].value));
                }
            }
        }

        if (!parenthesis_stack.empty())
        {

            std::string error_top = parenthesis_stack.top().value;
            throw std::runtime_error("Syntax Error : Missing Appropriate Parenthesis for " + error_top + " at the end of the file");
        }
        int total_machines = Identifier().identify(partial_unknown_tokens);
        auto known_tokens = partial_unknown_tokens;
        std::vector<int> mark_off_vector = {0, 0, 0, 0, 0, 0};
        for (int elem = 0; elem < known_tokens.size(); elem++)
        {
            std::vector<Token> token_collection = {};
            if (known_tokens[elem].type == Token::MACHINE_TOKEN)
            {
                int i = 0;
                while (known_tokens[i].type != Token::CBL_TOKEN)
                {
                    token_collection.push_back(known_tokens[i].type);
                    i++;
                }
                token_collection.push_back(Token::CBL_TOKEN);
                bool verified = Verifier().verify_grammar(token_collection, Grammar_Type::MACHINE_DEF_GRAMMAR);
                if (!verified)
                {
                    throw std::runtime_error("Syntax Error : Machine Definition Verification Failed");
                }
                else
                {
                    mark_off_vector[0] += 1;
                }
            }
            else if (known_tokens[elem].type == Token::CONSUMES_TOKEN)
            {

                while (known_tokens[elem].type != Token::CPR_TOKEN)
                {
                    token_collection.push_back(known_tokens[elem].type);
                    elem++;
                }
                token_collection.push_back(Token::CPR_TOKEN);
                bool verified = Verifier().verify_grammar(token_collection, Grammar_Type::CONSUMES_DEF_GRAMMAR);
                if (!verified)
                {
                    throw std::runtime_error("Syntax Error : Consumes Definition Verification Failed");
                }
                else
                {
                    mark_off_vector[1] += 1;
                }
            }
            else if (known_tokens[elem].type == Token::TAPE_TOKEN)
            {
                while (known_tokens[elem].type != Token::CPR_TOKEN)
                {
                    token_collection.push_back(known_tokens[elem].type);
                    elem++;
                }
                token_collection.push_back(Token::CPR_TOKEN);
                bool verified = Verifier().verify_grammar(token_collection, Grammar_Type::TAPE_DEF_GRAMMAR);
                if (!verified)
                {
                    throw std::runtime_error("Syntax Error : Tape Definition Verification Failed");
                }
                else
                {
                    mark_off_vector[2] += 1;
                }
            }
            else if (known_tokens[elem].type == Token::DEF_TOKEN)
            {
                while (known_tokens[elem].type != Token::IGNORE_UNKNOWNS_TOKEN)
                {
                    token_collection.push_back(known_tokens[elem].type);
                    elem++;
                }
                elem--;
                bool verified = Verifier().verify_grammar(token_collection, Grammar_Type::DEF_DEF_GRAMMAR);
                if (!verified)
                {
                    throw std::runtime_error("Syntax Error : Def Definition Verification Failed");
                }
                else
                {
                    mark_off_vector[3] += 1;
                }
            }
            else if (known_tokens[elem].type == Token::IGNORE_UNKNOWNS_TOKEN)
            {
                while (known_tokens[elem].type != Token::CPR_TOKEN)
                {
                    token_collection.push_back(known_tokens[elem].type);
                    elem++;
                }
                token_collection.push_back(Token::CPR_TOKEN);
                bool verified = Verifier().verify_grammar(token_collection, Grammar_Type::IGNORE_UNKNOWNS_DEF_GRAMMAR);
                if (!verified)
                {
                    throw std::runtime_error("Syntax Error : Ignore Unknowns Definition Verification Failed");
                }
                else
                {
                    mark_off_vector[4] += 1;
                }
            }
            else if (known_tokens[elem].type == Token::RELAY_TOKEN)
            {
                while (known_tokens[elem].type != Token::CBR_TOKEN)
                {
                    token_collection.push_back(known_tokens[elem].type);
                    elem++;
                }
                token_collection.push_back(Token::CBR_TOKEN);
                bool verified = Verifier().verify_grammar(token_collection, Grammar_Type::RELAY_DEF_GRAMMAR);
                if (!verified)
                {
                    throw std::runtime_error("Syntax Error : Relay Definition Verification Failed");
                }
                else
                {
                    mark_off_vector[5] += 1;
                }
            }
        }
        for (auto i : mark_off_vector)
        {
            if (i != total_machines)
            {
                throw std::runtime_error("Syntax Error : One or more components are missing from one or more machines");
            }
        }
        // rephrase changed tokens back . (direction and decision tokens)
        for (int i = 0; i < known_tokens.size(); i++)
        {
            if (known_tokens[i].type == Token::DECISION_TOKEN)
            {
                if (known_tokens[i].value == "accept")
                {
                    known_tokens[i].type = Token::ACCEPT_TOKEN;
                }
                else
                {
                    known_tokens[i].type = Token::REJECT_TOKEN;
                }
            }
            else if (known_tokens[i].type == Token::TRANSITION_DIRECTION_TOKEN)
            {
                if (known_tokens[i].value == "<-")
                {
                    known_tokens[i].type = Token::TRANSITION_DIRECTION_LEFT_TOKEN;
                }
                else if (known_tokens[i].value == "->")
                {
                    known_tokens[i].type = Token::TRANSITION_DIRECTION_RIGHT_TOKEN;
                }
            }
        }
        return known_tokens;
    }
    catch (std::runtime_error e)
    {

        std::cout << e.what() << std::endl;
        exit(1);
    }

    return partial_unknown_tokens;
}

std::vector<Machine> parse(const std::vector<LEXER_Element> tokens)
{
    auto condensed_tokens = condensor(tokens);
    auto san_pri = sanitizer_primary(condensed_tokens);
    auto san_sec = sanitizer_secondary(san_pri);
    // enough verification confidence is achieved with secondary sanitizer and now
    // the machines can be actually built and returned

    std::vector<Machine> GENERATED_machines;
    for (int i = 0; i < san_sec.size(); i++)
    {
        if (san_sec[i].type == Token::MACHINE_NAME_TOKEN)
        {
            Machine temp_machine(san_sec[i].value);

            while (san_sec[i].type != Token::MACHINE_TOKEN)
            {
                if (san_sec[i].type == Token::CONSUMES_TOKEN)
                {
                    if (san_sec[i + 3].type == Token::NULL_TOKEN)
                    {
                        temp_machine.consumes = Consumes();
                        i++;
                    }
                    else
                    {
                        std::vector<Machine> temp_consumes;
                        while (san_sec[i].type != Token::CPR_TOKEN)
                        {
                            if (san_sec[i].type == Token::EXTERNAL_TURING_MACHINE_NAME_TOKEN)
                            {
                                temp_consumes.push_back(Machine(san_sec[i].value));
                            }
                            i++;
                        }
                        temp_machine.consumes = Consumes(temp_consumes);
                    }
      
                }
                else if (san_sec[i].type == Token::TAPE_TOKEN)
                {
                    i += 3;
              
                    while (san_sec[i].type != Token::CPR_TOKEN)
                    {

                        if (san_sec[i].type == Token::TAPE_NAME_TOKEN)
                        {
                            Tape * tape_ref =  nullptr; 
                            if(san_sec[i+2].value == "#_#")
                            {
                                tape_ref = new Tape(san_sec[i].value ,"#",0, true);
                            }
                            else
                            {
                                tape_ref = new Tape(san_sec[i].value, san_sec[i + 2].value);
                            }
                            temp_machine.ref_tapes.push_back(tape_ref);
                            i += 2;
                        }
                        i++;
                    }
                    
                
                }
                else if (san_sec[i].type == Token::DEF_TOKEN)
                {
                    std::vector<Transition> temp_transitions;
                    std::vector<State> temp_states;
                    std::vector<Symbol> temp_symbols;
                    std::vector<State> temp_final_states;
                    State temp_initial_state;
                    Symbol temp_blank_symbol;

                    while (san_sec[i].type != Token::IGNORE_UNKNOWNS_TOKEN)
                    {
                        if (san_sec[i].type == Token::STATE_TOKEN)
                        {
                            temp_states.push_back(State(san_sec[i].value));
                        }
                        else if (san_sec[i].type == Token::INPUT_SYMBOL_TOKEN)
                        {
                            temp_symbols.push_back(Symbol(san_sec[i].value, Subtype::INPUT_SYMBOL));
                        }
                        else if (san_sec[i].type == Token::INITIAL_STATE_TOKEN)
                        {
                            temp_initial_state = State(san_sec[i].value);
                        }
                        else if (san_sec[i].type == Token::FINAL_STATE_TOKEN)
                        {
                            temp_final_states.push_back(State(san_sec[i].value, true));
                        }
                        else if (san_sec[i].type == Token::BLANK_SYMBOL_TOKEN)
                        {
                            temp_blank_symbol = Symbol(san_sec[i].value, Subtype::BLANK_SYMBOL);
                        }
                        else if (san_sec[i].type == Token::TRANS_STATE_TOKEN)
                        {
                            temp_transitions.push_back(Transition(State(san_sec[i].value), Symbol(san_sec[i + 2].value, Subtype::READ_SYMBOL), State(san_sec[i + 4].value), Symbol(san_sec[i + 6].value, Subtype::WRITE_SYMBOL), Symbol(san_sec[i + 8].value, Subtype::TRANSITION_DIRECTION_SYMBOL), Tape(san_sec[i + 10].value), Tape(san_sec[i + 12].value)));
                            i += 13;
                        }
                        i++;
                    }
                    temp_machine.states = temp_states;
                    temp_machine.symbols = temp_symbols;
                    temp_machine.initial_state = temp_initial_state;
                    temp_machine.final_states = temp_final_states;
                    temp_machine.blank_symbol = temp_blank_symbol;
                    temp_machine.transitions = temp_transitions;
          
                    i--;
                }
                else if (san_sec[i].type == Token::IGNORE_UNKNOWNS_TOKEN)
                {
                    temp_machine.ignore_unknowns = san_sec[i + 3].value == "accept" ? true : false;
                    i += 3;
                 
                }
                else if (san_sec[i].type == Token::RELAY_TOKEN)
                {
                    Relay temp_relay;
                    std::vector<Machine> on_accept;
                    std::vector<Machine> on_reject;
                    i += 6;
                    while (san_sec[i].type != Token::CPR_TOKEN)
                    {
                        if (san_sec[i].type == Token::CONSOLE_TOKEN)
                        {
                            temp_relay.relay_to_console_on_accept = true;
                        }
                        else if (san_sec[i].type == Token::EXTERNAL_TURING_MACHINE_NAME_TOKEN)
                        {
                            on_accept.push_back(Machine(san_sec[i].value));
                        }
                        i++;
                    }
                    i += 4;
                    while (san_sec[i].type != Token::CPR_TOKEN)
                    {
                        if (san_sec[i].type == Token::CONSOLE_TOKEN)
                        {
                            temp_relay.relay_to_console_on_reject = true;
                        }
                        else if (san_sec[i].type == Token::EXTERNAL_TURING_MACHINE_NAME_TOKEN)
                        {
                            on_reject.push_back(Machine(san_sec[i].value));
                        }
                        i++;
                    }
                    temp_relay.to_relay_machine_on_accept = on_accept;
                    temp_relay.to_relay_machine_on_reject = on_reject;
                    temp_machine.relay = temp_relay;
                
                    break; 
                }
                i++;
            }
            GENERATED_machines.push_back(temp_machine);
        }
    }
    return GENERATED_machines;
}

