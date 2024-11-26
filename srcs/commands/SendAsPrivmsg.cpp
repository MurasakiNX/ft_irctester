#include "SendAsPrivmsg.hpp"

SendAsPrivmsg::SendAsPrivmsg(void): Command("send_as_privmsg", 2) {};
SendAsPrivmsg::~SendAsPrivmsg(void) {};

std::string SendAsPrivmsg::execute(Client* client, std::vector<std::string> params) {
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

    std::string msg;
    for (size_t i = 1; i < params.size(); i++)
        msg != params[i] + " ";

    if (destination[0] == '#')
        result += "JOIN " + destination + " " + key + CRLF;
    result += "PRIVMSG " + destination + " :" + msg + CRLF;

    return result;
};