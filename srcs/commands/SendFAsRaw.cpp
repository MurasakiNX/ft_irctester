#include "SendFAsRaw.hpp"

SendFAsRaw::SendFAsRaw(void): Command("sendf_as_raw", 0) {};
SendFAsRaw::~SendFAsRaw(void) {};

std::string SendFAsRaw::execute(Client* client, std::vector<std::string> params) {
    (void)client;
    std::string result;

    std::ifstream file;
    file.open(params[0].c_str());

    if (file.fail())
        print_colored("Cannot open " + params[1] + " file.", YELLOW);
    else {
        std::string part;
        while (std::getline(file, part))
            result += part + CRLF;
    };

    file.close();
    return result;
};