#include "SendFAsPrivmsg.hpp"

SendFAsPrivmsg::SendFAsPrivmsg(void): Command("sendf_as_privmsg", 2) {};
SendFAsPrivmsg::~SendFAsPrivmsg(void) {};

std::string SendFAsPrivmsg::execute(Client* client, std::vector<std::string> params) {
    (void)client;
    std::string result;

    std::string fullDest = params[0];
    size_t pos = fullDest.find(',');

    std::string destination = fullDest;
    std::string key = "";

    if (pos != std::string::npos) {
        destination = destination.substr(0, pos);
        key = fullDest.substr(pos + 1);
    };

    std::ifstream file;
    file.open(params[1].c_str());

    if (file.fail())
        print_colored("Cannot open " + params[1] + " file.", YELLOW);
    else {
        if (destination[0] == '#')
            result += "JOIN #" + destination + " " + key + CRLF;

        std::string part;
        while (std::getline(file, part))
            result += "PRIVMSG " + destination + " :" + part + CRLF;
    };

    file.close();
    return result;
};