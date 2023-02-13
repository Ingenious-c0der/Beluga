#ifndef TAPE_H
#define TAPE_H
#include <string>
#include <iostream>
#include "../types.h"
class Tape
{
    int current_index;
    std::string name;
    std::string tape_contents;
    std::string current;
    bool is_reference = false; 
    friend class Machine ;
    friend class Transition; 

public:
    Tape(); // default constructor
    Tape(std::string, std::string, int);
    Tape(std::string); // for forward references
    void move_left();
    void move_right();
    std::string get_current();
    std::string get_name();
    void update_current(std::string);
};

Tape::Tape()
{
    this->name = "tape_undefined";
    this->tape_contents = "";
    this->current_index = 0;
    this->current = "$";

}

Tape::Tape(std::string name, std::string tape_contents,int index = 0)
{
    this->name = name;
    this->tape_contents = tape_contents;
    this->tape_contents.insert(0, "$");
    this->tape_contents.append("$");
    this->current_index = index + 1;
    // allow for dynamic tape expansion later ,right now its LBA tape
}
Tape::Tape(std::string name)
{
    this->name = name;
    this->is_reference = true;
}

std::string Tape::get_name()
{
    return this->name;
}

void Tape::move_left()
{
    try
    {
        if (current_index == 0)
        {
            throw ERROR_TYPES::TAPE_OVERFLOW_ACCESS_LEFT;
        }
        else
        {
            current_index--;
          
        }
    }
    catch (ERROR_TYPES e)
    {
        std::cout << "An Error Occured while trying to move left on the tape : " << this->name <<" " << stringify(e) << std::endl;
        exit(1); // exit with error
    }
}
void Tape::move_right()
{
    try
    {
        if (current_index == tape_contents.length())
        {
            throw ERROR_TYPES::TAPE_OVERFLOW_ACCESS_RIGHT;
        }
        else
        {
            current_index++;
            
        }
    }
    catch (ERROR_TYPES e)
    {
        std::cout << "An Error Occured while trying to move right on the tape : " << this->name <<" "<< stringify(e) << std::endl;
        exit(1); // exit with error
    }
}

void Tape::update_current(std::string new_current)
{
  
    this->tape_contents[current_index] = new_current[0];
}

std::string Tape::get_current()
{
    return std::string(1,tape_contents[current_index]);
}

#endif