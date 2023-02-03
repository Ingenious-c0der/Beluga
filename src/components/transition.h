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
    //transit() function 
    bool does_match(State St,Symbol s ,Tape t)
    {
        if(this->currentState.name == St.name && this->input_symbol.name == s.name && this->currentTape.name == t.name)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    friend class Machine ;

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

//can be used later in run of machine for each transition rather than inplace handling 
// class Transit_feedback
// {
    
//     public:
//     State switchToState; 

// };


#endif
