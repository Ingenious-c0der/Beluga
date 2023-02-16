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
    bool is_infinite = false;
    friend class Machine;
    friend class Transition;

public:
    Tape(); // default constructor
    Tape(std::string, std::string, int, bool);
    Tape(std::string); // for forward references
    void move_left();
    void move_right();
    std::string get_current();
    std::string get_name();
    std::string display();
    void update_current(std::string);
    void reset();
};

Tape::Tape()
{
    this->name = "tape_undefined";
    this->tape_contents = "";
    this->current_index = 0;
    this->current = "$";
}

Tape::Tape(std::string name, std::string tape_contents, int index = 0, bool is_infinite = false)
{
    this->name = name;
    this->tape_contents = tape_contents;
    this->is_infinite = is_infinite;

    if (is_infinite)
    {
        this->tape_contents = std::string(20, '#');
        this->current_index = 10;
    }
    else
    {
        this->current_index = index + 1;
    }
    this->tape_contents.insert(0, "$");
    this->tape_contents.append("$");
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
        if (is_infinite && current_index == 1)
        {

            this->tape_contents.insert(1, std::string(10, '#'));
            this->current_index = 10;
        }
        else if (current_index == 0)
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
        std::cout << "An Error Occured while trying to move left on the tape : " << this->name << " " << stringify(e) << std::endl;
        exit(1); // exit with error
    }
}
void Tape::move_right()
{
    try
    {

        if (is_infinite && current_index == tape_contents.length() - 2)
        {
            this->tape_contents.insert(tape_contents.length() - 1, std::string(10, '#'));
            current_index++;
        }

        else if (current_index == tape_contents.length())
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
        std::cout << "An Error Occured while trying to move right on the tape : " << this->name << " " << stringify(e) << std::endl;
        exit(1); // exit with error
    }
}

std::string Tape::display()
{
    if (!is_infinite)
        return tape_contents.substr(1, tape_contents.length() - 2);
    int max_traversed_left = 1;
    int max_traversed_right = tape_contents.length() - 2;

    while (tape_contents[max_traversed_left] == '#')
    {
        max_traversed_left++;
    }; // find first non # character
    while (tape_contents[max_traversed_right] == '#')
    {
       
        max_traversed_right--;
    }; // find first non # character
    return tape_contents.substr(max_traversed_left, max_traversed_right - max_traversed_left + 1);
}

void Tape::update_current(std::string new_current)
{

    this->tape_contents[current_index] = new_current[0];
}

void Tape::reset()
{
    if (!is_infinite)
        this->current_index = 1;
    else
        this->current_index = 10;
}

std::string Tape::get_current()
{
    return std::string(1, tape_contents[current_index]);
}

#endif