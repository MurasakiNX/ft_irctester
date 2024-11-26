#include "ft_irctester.hpp"

std::vector<std::string> split(std::string const& str, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream stream(str);
    while (std::getline(stream, token, delimiter))
        tokens.push_back(token);
    return tokens;
};