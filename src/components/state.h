#ifndef STATE_H
#define STATE_H
#include <iostream>
#include <map>
#include <vector>

class State
{
    std::string name = "state_undefined";
    std::vector<State> next_states;

public:
    State();
    State(std::string, std::vector<State>);
    bool is_valid_next(State s)
    {
        for (int i = 0; i < next_states.size(); i++)
        {
            if (next_states[i].name == s.name)
            {
                return true;
            }
        }
        return false;
    }
};
State::State()
{
    this->name = "state_undefined";
    this->next_states = {};
}

State::State(std::string, std::vector<State>)
{
    this->name = name;
    this->next_states = next_states;
}

#endif;