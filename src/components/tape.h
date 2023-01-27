#ifndef TAPE_H
#define TAPE_H
#include <string>
#include <iostream>
#include "../types.h"
class Tape
{
    int current_index;
    bool is_final;
    std::string name;
    std::string tape_contents;
    std::string current;

public:
    Tape(); // default constructor
    Tape(std::string, std::string, bool, int);
    char *move_left();
    char *move_right();
    std::string get_current();
    bool get_is_final();
    void update_current(std::string);
};

Tape::Tape()
{
    this->name = "tape_undefined";
    this->is_final = false;
    this->tape_contents = "";
    this->current_index = 0;
    this->current = "";
}

Tape::Tape(std::string name, std::string tape_contents, bool is_final, int index = 0)
{
    this->name = name;
    this->is_final = is_final;
    this->tape_contents = tape_contents;
    this->tape_contents.insert(0, "$");
    this->tape_contents.append("$");
    this->current_index = index + 1;
    this->current = tape_contents[index + 1];
    // allow for dynamic tape expansion later ,right now its LBA tape
}

char *Tape::move_left()
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
            current = tape_contents[current_index];
        }
    }
    catch (ERROR_TYPES e)
    {
        std::cout << "An Error Occured while trying to move left on the tape : " << this->name << stringify(e) << std::endl;
        exit(1); // exit with error
    }
}
char *Tape::move_right()
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
            current = tape_contents[current_index];
        }
    }
    catch (ERROR_TYPES e)
    {
        std::cout << "An Error Occured while trying to move right on the tape : " << this->name << stringify(e) << std::endl;
        exit(1); // exit with error
    }
}

void Tape::update_current(std::string new_current)
{
    this->current = new_current;
}



std::string Tape::get_current()
{
    return current;
}

bool Tape::get_is_final()
{
    return is_final ? true : false;
}

#endif;