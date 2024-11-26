#include "Command.hpp"

Command::Command(std::string name, int requiredParamsNumber): _name(name), _requiredParamsNumber(requiredParamsNumber) {
    print_colored("[COMMAND LOADED] " + name + " command loaded successfully!", CYAN);
};

Command::~Command(void) {};

// Getters
std::string const& Command::getName(void) {
    return this->_name;
};

int const& Command::getRequiredParamsNumber(void) {
    return this->_requiredParamsNumber;
};