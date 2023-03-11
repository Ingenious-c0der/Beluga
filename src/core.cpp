#include <vector>
#include "parser.cpp"
#include <algorithm>
// -. check if machine names are unique
// 1. find if any tm's forward reference is not present
// 2. Resolve topological ordering using relay and cosumes
// 3. check if tape names in each machine are unique and valid
// 4. check if state names in each machine are unique and valid
// 5 . check ignore unknowns for symbol sensitivity
// 6. If everything is valid, execute the machines in topological order

class Resolution_Pair
{
public:
    Machine before;
    Machine after;
    int marked = 0;
    Resolution_Pair()
    {
        this->before = Machine();
        this->after = Machine();
    }
    Resolution_Pair(Machine before, Machine after)
    {
        this->before = before;
        this->after = after;
    }
};

class RP_CONTAINER
{
public:
    std::vector<Resolution_Pair> pairs;
    RP_CONTAINER()
    {
        this->pairs = {};
    }
    RP_CONTAINER(std::vector<Resolution_Pair> pairs)
    {
        this->pairs = pairs;
    }
    void add_pair(Resolution_Pair pair)
    {
        this->pairs.push_back(pair);
    }

    bool search_after(Machine m)
    {
        for (auto pair : this->pairs)
        {
            if (pair.after.name == m.name)
            {
                return true;
            }
        }
        return false;
    }

    bool search_before(Machine m)
    {
        for (auto pair : this->pairs)
        {
            if (pair.before.name == m.name)
            {
                return true;
            }
        }
        return false;
    }
    std::vector<Machine> get_afters()
    {
        std::vector<Machine> afters;
        for (auto pair : this->pairs)
        {
            afters.push_back(pair.after);
        }
        return afters;
    }
    std::vector<Machine> get_befores()
    {
        std::vector<Machine> befores;
        for (auto pair : this->pairs)
        {
            befores.push_back(pair.before);
        }
        return befores;
    }

    void remove_pair_where_after_name(std::string name)
    {
        //220 iq or -220 iq ?  removing while iterating in for loop was the biggest PITA
        int counter = 0;
        int active_pair_size = this->pairs.size();
        while (true)
        {
            if (counter == active_pair_size)
            {
                break;
            }
            if (this->pairs[counter].after.name == name)
            {
                this->pairs.erase(this->pairs.begin() + counter);
                active_pair_size = this->pairs.size();
                counter = 0;
                continue;
            }
            counter++;
        }
    }
    void remove_pair_where_before_name(std::string name)
    {
        int counter = 0;
        int active_pair_size = this->pairs.size();
        while (true)
        {
            if (counter == active_pair_size)
            {
                break;
            }
            if (this->pairs[counter].before.name == name)
            {
                this->pairs.erase(this->pairs.begin() + counter);
                active_pair_size = this->pairs.size();
                counter = 0;
                continue;
            }
            counter++;
        }
    }

    // void print_pairs()
    // {
    //     for (auto pair : this->pairs)
    //     {
    //         std::cout << pair.before.name << " -> " << pair.after.name << std::endl;
    //     }
    // }
};

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

void combine_tapes(std::string ext_mac_name, std::vector<Tape*> tapes_2 , std::vector<Machine> & machines)
{

    int ext_mac_index = -1;
    for (int i = 0; i < machines.size(); i++)
    {
        if (machines[i].name == ext_mac_name)
        {
            ext_mac_index = i;
            break;
        }
    }
    if(ext_mac_index == -1)
    {
        std::string error_name = "Machine name " + ext_mac_name + " is not found while combining tapes";
        throw std::runtime_error(error_name);
    }
    for(auto t: machines[ext_mac_index].ref_tapes)
    {
        if(t->get_name() == tapes_2[0]->get_name())
        {
            std::string error = "Error Tape Name Clash : Tape name " + t->get_name() + " is not unique while combining tapes for machine "+ ext_mac_name ;
            std::string resolve_error = "To resolve this error , please refer https://github.com/Ingenious-c0der/Beluga/blob/master/documentation.md#error--tape-name-clash-";
            std::cout << error << std::endl;
            std::cout << resolve_error << std::endl;
            exit(1);
        }
    }


    for (auto tape : tapes_2)
    {
        machines[ext_mac_index].ref_tapes.push_back(tape);
    }
}

bool not_in(int n, std::vector<int> nums)

{
    for (auto num : nums)
    {
        if (num == n)
        {
            return false;
        }
    }
    return true;
}

Machine get_machine_by_name(std::string name, std::vector<Machine> machines)
{
    for (auto machine : machines)
    {
        if (machine.name == name)
        {
            return machine;
        }
    }
    std::string error_name = "Machine name " + name + " is not found while fetching machine by name";
    throw std::runtime_error(error_name);
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
    if(machines.size() == 0)
    {
        return sorted_machines;
    }
    else if(machines.size() == 1)
    {
        sorted_machines.push_back(machines[0]);
        return sorted_machines;
    }
    RP_CONTAINER container;
    for (int i = 0; i < machines.size(); i++)
    {
        //remember ext_mac is not an actual machine, it is just a name reference
        for (auto ext_mac : machines[i].relay.to_relay_machine_on_accept)
        {
            if (machine_exists_and_consumes(ext_mac, machines[i], machines))
            {
                combine_tapes(ext_mac.name, machines[i].ref_tapes , machines);
                container.add_pair(Resolution_Pair(machines[i], get_machine_by_name(ext_mac.name, machines)));
               
            }
        }
        for (auto ext_mac : machines[i].relay.to_relay_machine_on_reject)
        {
            if (machine_exists_and_consumes(ext_mac, machines[i], machines))
            {
                //std::cout << "Machine " << machines[i].name << " relays to " << ext_mac.name << " on reject" << std::endl;
                combine_tapes(ext_mac.name, machines[i].ref_tapes , machines);
                container.add_pair(Resolution_Pair(machines[i],get_machine_by_name(ext_mac.name, machines)));
               
            }
        }
    }
    bool sorted = false;
    std::vector<Machine> GROSSLY_DEPENDENT_MACHINES;
    std::vector<Machine> BEFORE = container.get_befores();
    std::vector<Machine> AFTER = container.get_afters();
    for (int i = 0; i < AFTER.size(); i++)
    {
        if (not_in(AFTER[i], BEFORE, GROSSLY_DEPENDENT_MACHINES))
        {
            GROSSLY_DEPENDENT_MACHINES.push_back(AFTER[i]);
        }
    }
   // std::cout<< "Grossly dependent machines: "<< GROSSLY_DEPENDENT_MACHINES.size() << std::endl;

    int initial_size = machines.size() - GROSSLY_DEPENDENT_MACHINES.size();
   // std::cout << "Initial size: " << initial_size << std::endl;
    //std::cout << "Topological sorting" << std::endl;

    std::vector<std::string> buffer_name_machines;
    while (!sorted)
    {
        for (int i = 0; i < container.pairs.size(); i++)
        {

            if (not_in(container.pairs[i].before, container.get_afters(), sorted_machines))
            {
                sorted_machines.push_back(container.pairs[i].before);
                buffer_name_machines.push_back(container.pairs[i].before.name);
            }
        }

        if (sorted_machines.size() == 0 || buffer_name_machines.size() == 0)
        {
            if (initial_size == 0)
            {
                break;
            }
            std::cout << "Error: Cyclic dependency (Deadlock) detected for the following machines" << std::endl;
            for (auto mac : container.get_befores())
            {
                std::cout << mac.name << std::endl;
            }
            std::cout << "To resolve this error, refer https://github.com/Ingenious-c0der/Beluga/blob/master/documentation.md#error--cyclic-dependency-deadlock-detected-between-turing-machines-" << std::endl;
            exit(1);
        }
        else if (sorted_machines.size() == initial_size)
        {
            sorted = true;
        }
        else
        {
            // sweep marked names
            for (int i = 0; i < buffer_name_machines.size(); i++)
            {
                container.remove_pair_where_before_name(buffer_name_machines[i]);
            }
            buffer_name_machines.clear();
        }
    }
    // combine grossly dependent machines
    for (auto mac : GROSSLY_DEPENDENT_MACHINES)
    {
        sorted_machines.push_back(mac);
    }

    return sorted_machines;
}

void execute(std::string filename)
{
    auto x = lex(filename);
    std::vector<Machine> machines = parse(x);
    machine_unique_name_check(machines);
    machines = topo_sort(machines);
    for(auto machine : machines){
      
        machine.run();
    }
}

std::vector<Machine> import_pipeline(std::string filename, std::vector<std::string> machine_names)
{

}