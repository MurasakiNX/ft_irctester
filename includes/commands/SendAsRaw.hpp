#pragma once
#ifndef SENDASRAW_HPP
# define SENDASRAW_HPP

# include "Command.hpp"

class SendAsRaw : public Command {
    public:
        SendAsRaw(void);
        virtual ~SendAsRaw(void);

        virtual std::string execute(Client* client, std::vector<std::string> params);
};

#endif