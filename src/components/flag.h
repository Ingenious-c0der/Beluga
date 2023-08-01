#ifndef FLAGS_H
#define FLAGS_H

enum FLAG_TYPE{
    TIME_DEBUG,
    VERBOSE,
    HELP,
    VERSION,
    DEBUG
};
struct Flag{
    FLAG_TYPE type;
    bool value;
    Flag(FLAG_TYPE, bool);
}; 

Flag::Flag(FLAG_TYPE type, bool value)
{
    this->type = type;
    this->value = value;
}

#endif