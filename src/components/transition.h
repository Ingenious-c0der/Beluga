#ifndef TRANSITION_H
#define TRANSITION_H
#include "state.h"
#include "symbol.h"
#include  "tape.h"
//@data class 
class Transition{ 

    
    State currentState;
    Symbol input_symbol;
    Symbol output_symbol; 
    State nextState;
    Symbol Direction;
    Tape nextTape;
    Tape currentTape;
    public: 
    Transition(State,Symbol,State,Symbol,Symbol,Tape,Tape);

};  

Transition:: Transition(State currentState,Symbol input_symbol,State nextState,Symbol output_symbol,Symbol Direction,Tape currentTape,Tape nextTape)
{
    this->currentState = currentState;
    this->input_symbol = input_symbol;
    this->nextState = nextState;
    this->output_symbol = output_symbol;
    this->Direction = Direction;
    this->currentTape = currentTape;
    this->nextTape = nextTape;
}

#endif
