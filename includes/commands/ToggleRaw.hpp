#pragma once
#ifndef TOOGLERAW_HPP
# define TOOGLERAW_HPP

# include "Command.hpp"

class ToggleRaw : public Command {
    public:
        ToggleRaw(void);
        virtual ~ToggleRaw(void);

        virtual std::string execute(Client* client, std::vector<std::string> params);
};

#endif