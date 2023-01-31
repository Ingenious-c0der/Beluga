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

};
State::State()
{
    this->name = "state_undefined";

}

State::State(std::string, bool isFinal = false)
{
    this->name = name;
    this->isFinal = isFinal;
}

#endif