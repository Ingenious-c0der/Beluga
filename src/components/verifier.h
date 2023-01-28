#ifndef VERIFIER_H
#define VERIFIER_H
#include "lexer.h"
#include<vector>
//@semantic class, holds grammar for particular types
class Verifier
{


std::vector<Token> MACHINE_DEF_GRAMMAR = {Token::MACHINE_TOKEN, Token::CPL_TOKEN, Token::MACHINE_NAME_TOKEN , Token::CPR_TOKEN , Token::FAT_ARROW_TOKEN , Token::CBL_TOKEN   };
//consider comma tokens in pumping tokens
std::vector<Token> TAPE_DEF_GRAMMAR = {Token::TAPE_TOKEN, Token::COLON_TOKEN,  Token::CPL_TOKEN, Token::TAPE_PUMPING_TOKEN , Token::CPR_TOKEN };
std::vector<Token> TAPE_UNIT_DEF_GRAMMAR = {Token::CBL_TOKEN, Token::TAPE_NAME_TOKEN, Token::COMMA_TOKEN , Token::TAPE_CONTENTS_TOKEN,  Token::CBR_TOKEN };
std::vector<Token> TRANSITION_UNIT_DEF_GRAMMAR = {Token:: CPL_TOKEN , Token::STATE_TOKEN, Token::COMMA_TOKEN, Token::INPUT_SYMBOL_TOKEN, Token::COMMA_TOKEN , Token::OUTPUT_SYMBOL_TOKEN, Token::COMMA_TOKEN, Token::TRANSITION_DIRECTION_TOKEN, Token::COMMA_TOKEN, Token::STATE_TOKEN, Token::STATE_TOKEN, Token::CPR_TOKEN }; 
std::vector<Token> TRANSITION_DEF_GRAMMAR = {Token::CPL_TOKEN , Token::TRANSITION_PUMPING_TOKEN, Token::CPR_TOKEN };
std::vector<Token> Q_SET_DEF_GRAMMAR = {Token:: CBL_TOKEN, Token::Q_SET_PUMPING_TOKEN, Token::CBR_TOKEN }; 

public: 
 Verifier(); 
 Verifier(std::vector<LEXER_Element> , Token);
}; 

#endif