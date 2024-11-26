#include "Help.hpp"

Help::Help(void): Command("Help", 0) {};
Help::~Help(void) {};

std::string Help::execute(Client* client, std::vector<std::string> params) {
    (void)client;
    (void)params;
    print_info("TEST");
    return "";
};