#ifndef MACHINE_H
#define MACHINE_H
#include "export.h"
#include<vector>
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
    friend class Machine ;
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

class Machine
{
public:
    Consumes consumes;
    Relay relay;
    State initial_state;
    Symbol blank_symbol; 
    std::vector<Tape> tapes;
    std::vector<Transition> transitions;
    std::vector<State> states;
    std::vector<Symbol> symbols;
    std::vector<State> final_states;
    bool ignore_unknowns = false;
    bool is_forward_reference = true;
    bool run(); 
    std::string name;
    void to_string();
    Machine();
    Machine(std::string);
    Machine(Consumes, Relay, State, Symbol, std::vector<Tape>, std::vector<Transition>, std::vector<State>, std::vector<Symbol>, std::vector<State>, bool, bool);
};
Machine::Machine()
{

}
Machine::Machine(std::string name)
{
    this->name = name;
}
Machine::Machine(Consumes consumes, Relay relay, State initial_state, Symbol blank_symbol, std::vector<Tape> tapes, std::vector<Transition> transitions, std::vector<State> states, std::vector<Symbol> symbols, std::vector<State> final_states, bool ignore_unknowns, bool is_forward_reference)
{
    this->consumes = consumes;
    this->relay = relay;
    this->initial_state = initial_state;
    this->blank_symbol = blank_symbol;
    this->tapes = tapes;
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
    for (auto tape : this->tapes)
    {
        std::cout << tape.name << std::endl;
    }
    std::cout << "Transitions: " << std::endl;
    for (auto transition : this->transitions)
    {
        std::cout << transition.currentState.name << " " << transition.nextState.name << " " << transition.input_symbol.name << " " << transition.output_symbol.name<<" " << transition.Direction.name << std::endl;
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
bool Machine::run()
{
    //1. solve tape forward references while executing 
    //2. solve state forward references while executing
    //3. solve symbol forward references while executing
    



}
#endif