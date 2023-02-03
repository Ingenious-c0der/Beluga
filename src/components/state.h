#ifndef STATE_H
#define STATE_H
#include <iostream>
#include <map>
#include <vector>

class State
{
    std::string name = "state_undefined";

    bool isFinal = false;
public:
    State();
    State(std::string, bool);
    friend class Machine ;
    friend class Transition;
    

};
State::State()
{
    this->name = "state_undefined";

}

State::State(std::string name, bool isFinal = false)
{
    this->name = name;
    this->isFinal = isFinal;
}

#endif