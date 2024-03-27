#pragma once
#include "System.hpp"
#include "Node.hpp"
#include "NodePassword.hpp"

namespace Security {
    void initialize(Node * parent);
    std::string generateHash(std::string str);  
    std::string generateToken();
    std::string getDefaultPassword();
    bool checkToken(std::string token, std::string hash);
    bool hasPassword();
}
