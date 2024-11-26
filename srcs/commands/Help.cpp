#include "Help.hpp"

Help::Help(void): Command("help", 0) {};
Help::~Help(void) {};

std::string Help::execute(Client* client, std::vector<std::string> params) {
    (void)client;
    (void)params;
    print_colored("============================================================================== HELP =============================================================================", CYAN);
    print_colored("= [1]: /help: Prints the help message (The thing you are currently reading)                                                                                     =", CYAN);
    print_colored("= [2]: /send_as_privmsg <destination,key> <message>: Sends a PRIVMSG to the destination (If it's a channel, the key may be required)                            =", CYAN);
    print_colored("= [3]: /send_as_raw <message>: Sends a message to the server                                                                                                    =", CYAN);
    print_colored("= [4]: /sendf_as_privmsg <destination,key> <file>: Sends the content of a file as a PRIVMSG to the destination (If it's a channel, the key may be required)     =", CYAN);
    print_colored("= [5]: /sendf_as_raw <file>: Sends the content of a file as a message to the server                                                                             =", CYAN);
    print_colored("= [6]: /toggle_raw: Toogle raw system (If it is enabled, the tester will send as raw your messages if it does not start with /)                                 =", CYAN);
    print_colored("=================================================================================================================================================================", CYAN);
    return "";
};