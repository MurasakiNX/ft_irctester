#pragma once
#ifndef SENDASPRIVMSG_HPP
# define SENDASPRIVMSG_HPP

# include "Command.hpp"

class SendAsPrivmsg : public Command {
    public:
        SendAsPrivmsg(void);
        virtual ~SendAsPrivmsg(void);

        virtual std::string execute(Client* client, std::vector<std::string> params);
};

#endif