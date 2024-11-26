#pragma once
#ifndef SENDFASPRIVMSG_HPP
# define SENDFASPRIVMSG_HPP

# include "Command.hpp"

class SendFAsPrivmsg : public Command {
    public:
        SendFAsPrivmsg(void);
        virtual ~SendFAsPrivmsg(void);

        virtual std::string execute(Client* client, std::vector<std::string> params);
};

#endif