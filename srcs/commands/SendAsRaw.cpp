#include "SendAsRaw.hpp"

SendAsRaw::SendAsRaw(void): Command("send_as_raw", 1) {};
SendAsRaw::~SendAsRaw(void) {};

std::string SendAsRaw::execute(Client* client, std::vector<std::string> params) {
    (void)client;
    std::string result;

    for (size_t i = 0; i < params.size(); i++)
        result += params[i] + " ";

    return result + CRLF;
};
