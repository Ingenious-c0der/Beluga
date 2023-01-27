#ifndef DEF_H
#define DEF_H
#include <iostream>
#include <vector>
#include "state.h"
#include "symbol.h"
#include "tape.h"
#include "transition.h"
class Define
{

    std::vector<State> states;
    std::vector<Symbol> input_symbols;
    std::vector<Symbol> output_symbols;
    std::vector<Transition> transitions;
    State initial_state;
    Symbol blank_symbol;
    std::vector<State> final_states;

public:
    Define();
    Define(std::vector<State>, std::vector<Symbol>, std::vector<Transition>, State, Symbol, std::vector<State>);
};
Define::Define()
{
    this->states = {};
    this->input_symbols = {};
    this->transitions = {};
    this->initial_state = State();
    this->blank_symbol = Symbol();
    this->final_states = {};
}

Define::Define(std::vector<State> states, std::vector<Symbol> input_symbols, std::vector<Transition> transitions, State initial_state, Symbol blank_symbol, std::vector<State> final_states)
{
    this->states = states;
    this->input_symbols = input_symbols;
    this->transitions = transitions;
    this->initial_state = initial_state;
    this->blank_symbol = blank_symbol;
    this->final_states = final_states;
}

#endif;