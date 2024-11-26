#pragma once
#ifndef COMMAND_HPP
# define COMMAND_HPP

# include <string>
# include <vector>

class Client;
class Command {
    private:
        std::string     _name;
        int             _requiredParamsNumber;

    public:
        Command(std::string name, int requiredParamsNumber);
        virtual ~Command(void);

        // Getters
        std::string const& getName(void);
        int const& getRequiredParamsNumber(void);

        // Execute
        virtual std::string execute(Client* client, std::vector<std::string> params) = 0;
};

# include "Client.hpp"
# include "ft_irctester.hpp"

#endif