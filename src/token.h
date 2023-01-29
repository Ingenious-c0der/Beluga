#ifndef TOKEN_H
#define TOKEN_H
enum class Token
{

    CBL_TOKEN, // curved bracket left
    CBR_TOKEN, // curved bracket right
    CPL_TOKEN, // curved parenthesis left
    CPR_TOKEN, // curved parenthesis right
    FORWARD_SLASH_TOKEN,
    COMMA_TOKEN,
    TRANSITION_DIRECTION_RIGHT_TOKEN,
    TRANSITION_DIRECTION_LEFT_TOKEN,
    TAPE_NAME_TOKEN,
    TAPE_CONTENTS_TOKEN,
    TAPE_TOKEN, 
    CONSUMES_TOKEN,
    RELAY_TOKEN,
    DEF_TOKEN,
    BLANK_SYMBOL_TOKEN,
    ACCEPT_TOKEN,
    REJECT_TOKEN,
    IGNORE_UNKNOWNS_TOKEN,
    TRANSITION_START_TOKEN, // CAN BE REMOVED LATER
    TRANSITION_END_TOKEN,   // CAN BE REMOVED LATER
    UNKNOWN_SYMBOL_TOKEN,
    FINAL_STATE_TOKEN,
    INPUT_SYMBOL_TOKEN,
    INITIAL_STATE_TOKEN,
    ON_ACCEPT_TOKEN,
    ON_REJECT_TOKEN,
    MACHINE_TOKEN,
    MACHINE_NAME_TOKEN,
    FAT_ARROW_TOKEN,
    COLON_TOKEN,
    DASH_TOKEN,
    UNKNOWN_CONDENSED_TOKEN, 
    ARROW_RIGHT_TOKEN, 
    ARROW_LEFT_TOKEN,
    NULL_TOKEN, 
    ASTERISK_TOKEN,
    CONSOLE_TOKEN, 
    TAPE_PUMPING_TOKEN,
    STATE_TOKEN,
    OUTPUT_SYMBOL_TOKEN,
    TRANSITION_DIRECTION_TOKEN, 
    TRANSITION_PUMPING_TOKEN ,
    Q_SET_PUMPING_TOKEN, 
    STATE_PUMPING_TOKEN,
    SIGMA_SET_PUMPING_TOKEN,
    FINAL_STATE_PUMPING_TOKEN,
    OUTPUT_CONFIG_TOKEN ,
    CONSUMES_PUMPING_TOKEN, 
    Q_SET_DEF_TOKEN, 
    SIGMA_DEF_TOKEN,
    TRANSITION_DEF_TOKEN, 
    INITIAL_STATE_DEF_TOKEN,
    BLANK_SYMBOL_DEF_TOKEN,
    FINAL_STATE_DEF_TOKEN,
    EXTERNAL_TURING_MACHINE_NAME_TOKEN, 
    READ_SYMBOL_TOKEN, // for the tape read symbol in transitions
    WRITE_SYMBOL_TOKEN,
    DECISION_TOKEN,  // for the tape write symbol in transitions

};
// supports string conversion
constexpr const char *tokenToString(Token token)
{
    switch (token)
    {
    case Token::CBL_TOKEN:
        return "CBL_TOKEN";
    case Token ::CBR_TOKEN:
        return "CBR_TOKEN";
    case Token::CPL_TOKEN:
        return "CPL_TOKEN";
    case Token::CPR_TOKEN:
        return "CPR_TOKEN";
    case Token::FORWARD_SLASH_TOKEN:
        return "FORWARD_SLASH_TOKEN";
    case Token ::COMMA_TOKEN:
        return "COMMA_TOKEN";
    case Token::TRANSITION_DIRECTION_RIGHT_TOKEN:
        return "TRANSITION_DIRECTION_RIGHT_TOKEN";
    case Token::TRANSITION_DIRECTION_LEFT_TOKEN:
        return "TRANSITION_DIRECTION_LEFT_TOKEN";
    case Token:: UNKNOWN_SYMBOL_TOKEN:
        return "UNKNOWN_SYMBOL_TOKEN";
    case Token:: FAT_ARROW_TOKEN:
        return "FAT_ARROW_TOKEN";
    case Token:: COLON_TOKEN : 
        return "COLON_TOKEN";
    case Token:: DASH_TOKEN : 
        return "DASH_TOKEN";
    case Token::UNKNOWN_CONDENSED_TOKEN: 
        return "UNKNOWN_CONDENSED_TOKEN";
    case Token::MACHINE_NAME_TOKEN:
        return "MACHINE_NAME_TOKEN";
    case Token:: MACHINE_TOKEN:
        return "MACHINE_TOKEN";
    case Token::ON_ACCEPT_TOKEN:
        return "ON_ACCEPT_TOKEN";
    case Token::ON_REJECT_TOKEN:
        return "ON_REJECT_TOKEN";
    case Token:: INITIAL_STATE_TOKEN:
        return "INITIAL_STATE_TOKEN";
    case Token:: INPUT_SYMBOL_TOKEN:
        return "INPUT_SYMBOL_TOKEN";
    case Token::RELAY_TOKEN:
        return "RELAY_TOKEN";
    case Token::CONSOLE_TOKEN:
        return "CONSOLE_TOKEN";
    case Token::CONSUMES_TOKEN:
        return "CONSUMES_TOKEN";
    case Token::ARROW_LEFT_TOKEN:
        return "ARROW_LEFT_TOKEN";
    case Token::ARROW_RIGHT_TOKEN:
        return "ARROW_RIGHT_TOKEN";
    case Token::NULL_TOKEN:
        return "NULL_TOKEN";
    case Token::DEF_TOKEN:
        return "DEF_TOKEN";
    case Token::BLANK_SYMBOL_TOKEN:
        return "BLANK_SYMBOL_TOKEN";
    case Token::ACCEPT_TOKEN:
        return "ACCEPT_TOKEN";
    case Token::REJECT_TOKEN:
        return "REJECT_TOKEN";
    case Token::TAPE_TOKEN:
        return "TAPE_TOKEN";
    case Token::ASTERISK_TOKEN:
        return "ASTERISK_TOKEN";
    case Token::READ_SYMBOL_TOKEN:
        return "READ_SYMBOL_TOKEN";
    case Token::WRITE_SYMBOL_TOKEN:
        return "WRITE_SYMBOL_TOKEN";
    case Token::EXTERNAL_TURING_MACHINE_NAME_TOKEN:
        return "EXTERNAL_TURING_MACHINE_NAME_TOKEN";
    case Token::DECISION_TOKEN:
        return "DECISION_TOKEN";
    case Token::FINAL_STATE_TOKEN:
        return "FINAL_STATE_TOKEN";
    case Token::OUTPUT_CONFIG_TOKEN:
        return "OUTPUT_CONFIG_TOKEN";
    case Token::STATE_TOKEN:
        return "STATE_TOKEN";
    case Token::TRANSITION_DIRECTION_TOKEN:
        return "TRANSITION_DIRECTION_TOKEN";
    case Token::TAPE_NAME_TOKEN:
        return "TAPE_NAME_TOKEN";
    case Token::TAPE_CONTENTS_TOKEN:
        return "TAPE_CONTENTS_TOKEN";
    case Token::IGNORE_UNKNOWNS_TOKEN:
        return "IGNORE_UNKNOWNS_TOKEN";
    default : 
        return "UNLISTED_TOKEN";
    }
}


enum class Grammar_Type {
 MACHINE_DEF_GRAMMAR ,
TAPE_DEF_GRAMMAR  ,
TAPE_UNIT_DEF_GRAMMAR ,
TRANSITION_UNIT_DEF_GRAMMAR ,
 TRANSITION_DEF_GRAMMAR ,
 Q_SET_DEF_GRAMMAR ,
 SIGMA_SET_DEF_GRAMMAR ,
 INTIAL_STATE_DEF_GRAMMAR ,
 BLANK_SYMBOL_DEF_GRAMMAR ,
 FINAL_STATE_DEF_GRAMMAR ,
 IGNORE_UNKNOWNS_DEF_GRAMMAR,
 RELAY_DEF_GRAMMAR  ,
 MACHINE_CONTENTS_GRAMMAR,
 CONSUMES_DEF_GRAMMAR , 
 DEF_DEF_GRAMMAR,

}; 


#endif