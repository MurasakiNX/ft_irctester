#pragma once
#ifndef HELP_HPP
# define HELP_HPP

# include "Command.hpp"

class Help : public Command {
    public:
        Help(void);
        virtual ~Help(void);

        virtual std::string execute(Client* client, std::vector<std::string> params);
};

#endif