#include "ToggleRaw.hpp"

ToggleRaw::ToggleRaw(void): Command("toggle_raw", 0) {};
ToggleRaw::~ToggleRaw(void) {};

std::string ToggleRaw::execute(Client* client, std::vector<std::string> params) {
    (void)params;
    client->setSendRawData(!client->wantsToSendRawData());
    if (client->wantsToSendRawData())
        print_colored("Send raw data has been enabled!", CYAN);
    else
        print_colored("Send raw data has been disabled!", CYAN);
    return "";
};