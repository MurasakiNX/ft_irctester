#pragma once
#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "ft_irctester.hpp"

class Command;
class Client {
    private:
        int         _fd;
        int         _port;
        bool        _sentBasicTesterData;
        bool        _sendRawData;
        std::string _password;
        std::string _inData;
        std::string _outData;

        std::map<std::string, Command*> _commands;
        std::vector<pollfd> _pollFds;
        
        static bool _isRunning;
        static int  _exitStatus;

    public:
        Client(std::string port, std::string password);

        // Getters
        int const& getFd(void);
        int const& getPort(void);
        bool const& hasSentBasicTesterData(void);
        bool const& wantsToSendRawData(void);
        std::string const& getPassword(void);
        std::string& getInData(void);
        std::string& getOutData(void);

        std::map<std::string, Command*>& getCommands(void);
        std::vector<pollfd>& getPollFds(void);

        bool const& isRunning(void);
        int const& getExitStatus(void);

        // Getters by value
        Command* getCommandByName(std::string name);

        // Setters
        void setFd(int fd);
        void setSentBasicTesterData(bool sentBasicTesterData);
        void setSendRawData(bool sendRawData);

        void setIsRunning(bool isRunning);
        void setExitStatus(int exitStatus);
        void setupSignals(void);
        void setupCommands(void);

        // Static
        static int validatePort(std::string port);
        static std::string validatePassword(std::string password);
        static void signalHandler(int status);
        static void setSocketOptions(int socketFd);
        static pollfd getPollFd(int fd);

        // Parser
        void parseOutData(void);

        // Exec
        std::string execParsedLine(std::string parsedLine);

        // Launcher
        void launch(void);
        void cleanup(void);
};

# include "Command.hpp"

#endif