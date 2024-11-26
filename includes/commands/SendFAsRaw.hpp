#pragma once
#ifndef SENDFASRAW_HPP
# define SENDFASRAW_HPP

# include "Command.hpp"

class SendFAsRaw : public Command {
    public:
        SendFAsRaw(void);
        virtual ~SendFAsRaw(void);

        virtual std::string execute(Client* client, std::vector<std::string> params);
};

#endif