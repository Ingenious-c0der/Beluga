#ifndef RELAY_H ;
#define RELAY_H ;
#include "machine.h"
#include <vector>

class Relay{
    std::vector<Machine> to_relay_machine_on_accept; 
    std::vector<Machine> to_relay_machine_on_reject;
    public:
        Relay();
        Relay(std::vector<Machine>, std::vector<Machine>);
       

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


#endif ;