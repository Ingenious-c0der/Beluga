#include <vector>
#include "parser.cpp"



    // -. check if machine names are unique
    // 1. find if any tm's forward reference is not present
    // 2. Resolve topological ordering using relay and cosumes
    // 3. check if tape names in each machine are unique and valid
    // 4. check if state names in each machine are unique and valid
    // 5 . check ignore unknowns for symbol sensitivity
    // 6. If everything is valid, execute the machines in topological order


void machine_unique_name_check(std::vector<Machine> machines)
{

    // O(N^2) , but any ways works on limited amounts of machines at once
    try
    {
        for (int i = 0; i < machines.size(); i++)
        {
            std::string name = machines[i].name;
            for (int j = 0; j < machines.size(); j++)
            {
                if (i == j)
                    continue;
                if (machines[j].name == name)
                {
                    std::string error_name = "Machine name " + name + " is not unique";
                    throw std::runtime_error(error_name);
                }
            }
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        exit(1);
    }

}

std::vector<Tape> combine_tapes(std::vector<Tape> tapes_1, std::vector<Tape> tapes_2)
{

    for (auto tape : tapes_2)
    {
        tapes_1.push_back(tape);
    }
    return tapes_1;
}

bool in_state_set(Machine m, State s)
{

    return true; 
}

bool in_tape_set(Machine m, Tape t)
{
    return true;
}

bool not_in(Machine m, std::vector<Machine> machines, std::vector<Machine> machines_2)
{
    for (auto machine : machines)
    {
        if (machine.name == m.name)
        {
            return false;
        }
    }
    for (auto machine : machines_2)
    {
        if (machine.name == m.name)
        {
            return false;
        }
    }
    return true;
}

bool machine_exists_and_consumes(Machine consumer, Machine relays, std::vector<Machine> machines)
{
    for (auto machine : machines)
    {
        if (machine.name == consumer.name)
        {
            for (auto consume : machine.consumes.consumed_machines)
            {
                if (consume.name == relays.name)
                {
                    return true;
                }
            }
            std::cout << "WARNING: Machine " << consumer.name << " does not consume " << relays.name << " ,for this relay to work make sure the machine to which tapes are relayed declares it in its consumes definition" << std::endl;
            return false;
        }
    }
    std::cout << "Machine " << consumer.name << " does not exist" << std::endl;
    exit(1);
    return false; 
}

std::vector<Machine> topo_sort(std::vector<Machine> machines)
{
    std::vector<Machine> sorted_machines;
    std::vector<Machine> BEFORE;
    std::vector<Machine> AFTER;
    for (int i = 0; i < machines.size(); i++)
    {
        for (auto ext_mac : machines[i].relay.to_relay_machine_on_accept)
        {
            if (machine_exists_and_consumes(ext_mac, machines[i], machines))
            {
                BEFORE.push_back(machines[i]);
                AFTER.push_back(ext_mac);
                ext_mac.tapes = combine_tapes(ext_mac.tapes, machines[i].tapes);
            }
        }
        for (auto ext_mac : machines[i].relay.to_relay_machine_on_reject)
        {
            if (machine_exists_and_consumes(ext_mac, machines[i], machines))
            {
                BEFORE.push_back(machines[i]);
                AFTER.push_back(ext_mac);
                ext_mac.tapes = combine_tapes(ext_mac.tapes, machines[i].tapes);
            }
        }
    }
    bool sorted = false;
    int initial_size = BEFORE.size();
    std::vector<bool> mark = std::vector<bool>(BEFORE.size(), false);
    while (!sorted)
    {

        for (int i = 0; i < BEFORE.size(); i++)
        {   
            //mark phase 
            if (not_in(BEFORE[i], AFTER , sorted_machines))
            {
                sorted_machines.push_back(BEFORE[i]);
                mark[i] = true;
            }
        }
        if(sorted_machines.size() == 0)
        {
            if(initial_size == 0)
            {
                break  ;
            }
            std::cout<< "Error: Cyclic dependency detected" << std::endl;
            exit(1);
        }
        else if(sorted_machines.size() == initial_size)
        {
            sorted = true;
        }
        else
        {
            //sweep phase
            for (int i = 0; i < mark.size(); i++)
            {
                if(mark[i])
                {
                    BEFORE.erase(BEFORE.begin() + i);
                    AFTER.erase(AFTER.begin() + i);
                    mark.erase(mark.begin() + i);
                }
            }
        }
    }
    //cout sorted machine sequence
    for (auto mac : sorted_machines)
    {
        std::cout << mac.name << std::endl;
    }
    return sorted_machines;
}

void execute(std::string filename)
{

    auto x = lex(filename);
    std::vector<Machine> machines = parse(x);
    machine_unique_name_check(machines);
    machines = topo_sort(machines);
}