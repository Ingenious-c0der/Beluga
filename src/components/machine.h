#ifndef MACHINE_H
#define MACHINE_H
#include "export.h"
#include <vector>
class Machine;
class Consumes
{

public:
    std::vector<Machine> consumed_machines;
    Consumes();
    Consumes(std::vector<Machine>);
    friend class Machine;
};

Consumes::Consumes()
{
    this->consumed_machines = {};
}

Consumes::Consumes(std::vector<Machine> consumed_machines)
{
    this->consumed_machines = consumed_machines;
}

class Relay
{

public:
    Relay();
    Relay(std::vector<Machine>, std::vector<Machine>);
    bool relay_to_console_on_accept = false;
    bool relay_to_console_on_reject = false;
    std::vector<Machine> to_relay_machine_on_accept;
    std::vector<Machine> to_relay_machine_on_reject;
    friend class Machine;
};

Relay::Relay()
{
    this->to_relay_machine_on_accept = {};
    this->to_relay_machine_on_reject = {};
}

Relay::Relay(std::vector<Machine> to_relay_machine_on_accept, std::vector<Machine> to_relay_machine_on_reject)
{
    this->to_relay_machine_on_accept = to_relay_machine_on_accept;
    this->to_relay_machine_on_reject = to_relay_machine_on_reject;
}

class TRANSITION_PAIR
{
    Tape t;
    Symbol s;
    State st;
    Symbol dir;

public:
    TRANSITION_PAIR(Tape, Symbol, State, Symbol);
    TRANSITION_PAIR(State, Symbol);
    friend class Machine;
};

TRANSITION_PAIR::TRANSITION_PAIR(Tape t, Symbol s, State st, Symbol dir)
{
    this->t = t;
    this->s = s;
    this->st = st;
    this->dir = dir;
}

TRANSITION_PAIR::TRANSITION_PAIR(State st, Symbol s)
{
    this->st = st;
    this->s = s;
}

class Machine
{
public:
    Consumes consumes;
    Relay relay;
    State initial_state;
    Symbol blank_symbol;
    std::vector<Tape *> ref_tapes;
    std::vector<Transition> transitions;
    std::vector<State> states;
    std::vector<Symbol> symbols;
    std::vector<State> final_states;
    bool ignore_unknowns = false;
    bool is_forward_reference = true;
    bool run();
    Symbol getSymbol(std::string);
    State getState(std::string);
    int get_ref_tape(std::string);
    bool in(std::string, std::vector<State>);
    std::string name;
    void to_string();
    Machine();
    Machine(std::string);
    Machine(Consumes, Relay, State, Symbol, std::vector<Tape *>, std::vector<Transition>, std::vector<State>, std::vector<Symbol>, std::vector<State>, bool, bool);
};
Machine::Machine()
{
}
Machine::Machine(std::string name)
{
    this->name = name;
}
Machine::Machine(Consumes consumes, Relay relay, State initial_state, Symbol blank_symbol, std::vector<Tape *> ref_tapes, std::vector<Transition> transitions, std::vector<State> states, std::vector<Symbol> symbols, std::vector<State> final_states, bool ignore_unknowns, bool is_forward_reference)
{
    this->ref_tapes = ref_tapes;
    this->consumes = consumes;
    this->relay = relay;
    this->initial_state = initial_state;
    this->blank_symbol = blank_symbol;

    this->transitions = transitions;
    this->states = states;
    this->symbols = symbols;
    this->final_states = final_states;
    this->ignore_unknowns = ignore_unknowns;
    this->is_forward_reference = is_forward_reference;
}

void Machine::to_string()
{
    std::cout << "Machine name: " << this->name << std::endl;
    std::cout << "Consumes: " << std::endl;
    for (auto machine : consumes.consumed_machines)
    {
        std::cout << machine.name << std::endl;
    }
    std::cout << "Relay: " << std::endl;
    std::cout << "Relay to console on accept: " << this->relay.relay_to_console_on_accept << std::endl;
    std::cout << "Relay to console on reject: " << this->relay.relay_to_console_on_reject << std::endl;
    std::cout << "Relay to machines on accept: " << std::endl;
    for (auto machine : this->relay.to_relay_machine_on_accept)
    {
        std::cout << machine.name << std::endl;
    }
    std::cout << "Relay to machines on reject: " << std::endl;
    for (auto machine : this->relay.to_relay_machine_on_reject)
    {
        std::cout << machine.name << std::endl;
    }
    std::cout << "Initial state: " << this->initial_state.name << std::endl;
    std::cout << "Blank symbol: " << this->blank_symbol.name << std::endl;
    std::cout << "Tapes: " << std::endl;
    for (auto tape : this->ref_tapes)
    {
        std::cout << tape->name << std::endl;
    }
    std::cout << "Transitions: " << std::endl;
    for (auto transition : this->transitions)
    {
        std::cout << transition.currentState.name << " " << transition.nextState.name << " " << transition.input_symbol.name << " " << transition.output_symbol.name << " " << transition.Direction.name << std::endl;
    }
    std::cout << "States: " << std::endl;
    for (auto state : this->states)
    {
        std::cout << state.name << std::endl;
    }
    std::cout << "Symbols: " << std::endl;
    for (auto symbol : this->symbols)
    {
        std::cout << symbol.name << std::endl;
    }
    std::cout << "Final states: " << std::endl;
    for (auto state : this->final_states)
    {
        std::cout << state.name << std::endl;
    }
}

State Machine::getState(std::string stateName)
{
    for (auto state : states)
    {
        if (state.name == stateName)
        {
            return state;
        }
    }
    return State();
}

int Machine::get_ref_tape(std::string tapeName)
{
    for (int i = 0; i < ref_tapes.size(); i++)
    {
        if (ref_tapes[i]->name == tapeName)
        {
            return i;
        }
    }
    std::cout << "Undefined Tape found in Transition : " << tapeName << std::endl;
    exit(1);
    return -1;
}

Symbol Machine::getSymbol(std::string symbolName)
{
    for (auto symbol : symbols)
    {
        if (symbol.name == symbolName)
        {
            return symbol;
        }
    }
    if (symbolName == blank_symbol.name)
    {
        return blank_symbol;
    }
    else if (symbolName == "$")
    {
        return Symbol("$", Subtype::DOLLAR_SYMBOL);
    }
    // cout error message
    std::cout << "Undefined Symbol found in Transition : " << symbolName << std::endl;
    exit(1);

    return Symbol();
}

bool Machine::in(std::string stateName, std::vector<State> states)
{
    for (auto state : states)
    {
        if (state.name == stateName)
        {
            return true;
        }
    }
    return false;
}

bool Machine::run()
{
    // 1. solve tape forward references while executing
    // 2. solve state forward references while executing
    // 3. solve symbol forward references while executing
    // 4. Run the turing machine based on transition sequence matching
    State currentState = this->initial_state;
    int current_tape_index = -1;
    // setting the current tape index to the tape seen in the first transition sequentially , should this work every time? brood.
    for (int i = 0; i < ref_tapes.size(); i++)
    {
        if (ref_tapes[i]->name == transitions[0].currentTape.name)
        {
            current_tape_index = i;
            break;
        }
    }
    if (current_tape_index == -1)
    {
        std::cout << "Error: Unkwown Tape name " << transitions[0].currentTape.name << std::endl;
        exit(1);
    }
    for (int i = 0; i < states.size(); i++)
    {
        if (in(states[i].name, final_states))
        {
            states[i].isFinal = true;
        }
    }
    bool completed = false;
    bool matched = false;
    bool rejected = false;
    while (!completed)
    {
        for (int i = 0; i < transitions.size(); i++)
        {
            Symbol current_symbol = getSymbol(ref_tapes[current_tape_index]->get_current());
            if (current_symbol.subtype == Subtype::DOLLAR_SYMBOL)
            {
               
                completed = true;
                rejected = true;
                std::cout << "Unexpectedly hit the hard tape end : '$' on tape " << transitions[i].currentTape.name << " while trying to move in " << transitions[i].Direction.name << " direction , to resolve this error refer https://github.com/Ingenious-c0der/Beluga/blob/master/documentation.md#---dollar-symbol " << std::endl;
                 break; 
            }
            else if (transitions[i].does_match(currentState, current_symbol, *ref_tapes[current_tape_index]))
            {
                matched = true;
                if (ignore_unknowns)
                {
                    ref_tapes[current_tape_index]->update_current(transitions[i].output_symbol.name);
                }
                else
                {
                    Symbol s = getSymbol(transitions[i].output_symbol.name); // added symbol existence check

                    if (s.subtype == Subtype::DOLLAR_SYMBOL)
                    {
                        completed = true;
                        rejected = true;
                        std::cout << "Unexpectedly hit the hard tape end : '$' on tape " << transitions[i].currentTape.name << " while trying to move in " << transitions[i].Direction.name << " direction , to resolve this error refer https://github.com/Ingenious-c0der/Beluga/blob/master/documentation.md#---dollar-symbol " << std::endl;
                    }
                    ref_tapes[current_tape_index]->update_current(s.name);
                }

                currentState = transitions[i].nextState;
                if (getState(currentState.name).isFinal)
                {
                    completed = true;
                }
                if (transitions[i].Direction.subtype == Subtype::TRANSITION_DIRECTION_SYMBOL)
                {
                    if (transitions[i].Direction.name == "->")
                    {
                        ref_tapes[current_tape_index]->move_right();
                    }
                    else if (transitions[i].Direction.name == "<-")
                    {
                        ref_tapes[current_tape_index]->move_left();
                    }
                }
                current_tape_index = get_ref_tape(transitions[i].nextTape.name);
            }
        }
        if (!matched)
        {
            std::cout << name << " : No transition found for current state (" << currentState.name << ") and symbol (" << ref_tapes[current_tape_index]->get_current() << ") ,exiting" << std::endl;
            rejected = true;
            completed = true;
        }
        matched = false;
    }
    if (rejected)
    {
        if (relay.relay_to_console_on_reject)
        {
            std::cout << name << " (Rejected) : " << std::endl;
            for (int i = 0; i < ref_tapes.size(); i++)
            {
                std::cout << ref_tapes[i]->name << " : " << ref_tapes[i]->display() << std::endl;
            }
        }
    }
    else
    {
        if (relay.relay_to_console_on_accept)
        {
            std::cout << name << " (Accepted) : " << std::endl;
            for (int i = 0; i < ref_tapes.size(); i++)
            {
                std::cout << ref_tapes[i]->name << " : " << ref_tapes[i]->display() << std::endl;
            }
        }
    }
    for (int i = 0; i < ref_tapes.size(); i++)
    {
        ref_tapes[i]->reset();
    }
    return true;
}
#endif
