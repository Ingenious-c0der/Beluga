#include<fstream> 
#include<iostream>
bool file_exists(const std::string& name) {
    std::ifstream f(name.c_str());
    return f.good();
}

bool file_empty(const std::string& name) {
    std::ifstream f(name.c_str());
    return f.peek() == std::ifstream::traits_type::eof();
}

bool extension_check(const std::string& name) {
    std::string ext = name.substr(name.find_last_of(".") + 1);
    if (ext == "beluga") {
        return true;
    }
    else {
        return false;
    }
}


void sanitize_file(const std::string& name) {
    if (!extension_check(name)) {
        std::cout << "Incorrect File extension , expected : (<filename>.beluga)" << std::endl;
        exit(1);
    }
    if (!file_exists(name)) {
        std::cout << "File does not exist / Not found on the specified path" << std::endl;
        exit(1);
    }
    if (file_empty(name)) {
        std::cout << "File is empty" << std::endl;
        exit(1);
    }
}