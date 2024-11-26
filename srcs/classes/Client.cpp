#include "Client.hpp"

bool Client::_isRunning = false;
int Client::_exitStatus = 0;

Client::Client(std::string port, std::string password): _sentBasicTesterData(false), _sendRawData(false) {
    this->_port = this->validatePort(port);
    this->_password = this->validatePassword(password);
};

// Getters
int const& Client::getFd(void) {
    return this->_fd;
};

int const& Client::getPort(void) {
    return this->_port;
};

bool const& Client::hasSentBasicTesterData(void) {
	return this->_sentBasicTesterData;
};

bool const& Client::wantsToSendRawData(void) {
	return this->_sendRawData;
};

std::string const& Client::getPassword(void) {
    return this->_password;
};

std::string& Client::getInData(void) {
    return this->_inData;
};

std::string& Client::getOutData(void) {
    return this->_outData;
};

std::map<std::string, Command*>& Client::getCommands(void) {
    return this->_commands;
};

std::vector<pollfd>& Client::getPollFds(void) {
    return this->_pollFds;
};

bool const& Client::isRunning(void) {
    return this->_isRunning;
};

int const& Client::getExitStatus(void) {
    return this->_exitStatus;
};

// Getters by value
Command* Client::getCommandByName(std::string name) {
	std::map<std::string, Command*>& commands = this->getCommands();
	std::map<std::string, Command*>::iterator it = commands.find(name);
	if (it != commands.end())
		return it->second;
	return NULL;
};

// Setters
void Client::setFd(int fd) {
    this->_fd = fd;
};

void Client::setSentBasicTesterData(bool sentBasicTesterData) {
	this->_sentBasicTesterData = sentBasicTesterData;
};

void Client::setSendRawData(bool sendRawData) {
	this->_sendRawData = sendRawData;
};

void Client::setIsRunning(bool isRunning) {
    this->_isRunning = isRunning;
};

void Client::setExitStatus(int exitStatus) {
    this->_exitStatus = exitStatus;
};

void Client::setupSignals(void) {
	struct sigaction action;
	bzero(&action, sizeof(action));
	action.sa_handler = this->signalHandler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;

	sigaction(SIGINT, &action, NULL);
	sigaction(SIGTERM, &action, NULL);
	sigaction(SIGQUIT, &action, NULL);
	signal(SIGTSTP, SIG_IGN);
};

void Client::setupCommands(void) {
	std::map<std::string, Command*>& commands = this->getCommands();

	commands.insert(std::pair<std::string, Command*>("help", new Help));
	commands.insert(std::pair<std::string, Command*>("send_as_privmsg", new SendAsPrivmsg));
	commands.insert(std::pair<std::string, Command*>("send_as_raw", new SendAsRaw));
	commands.insert(std::pair<std::string, Command*>("sendf_as_privmsg", new SendFAsPrivmsg));
	commands.insert(std::pair<std::string, Command*>("sendf_as_raw", new SendFAsRaw));
	commands.insert(std::pair<std::string, Command*>("toggle_raw", new ToggleRaw));
};

// Static
int Client::validatePort(std::string port) {
	if (port.empty())
		throw std::invalid_argument("Port number cannot be empty.");

	for (size_t i = 0; i < port.length(); i++) {
		if (!isdigit(port[i]))
			throw std::invalid_argument("Found unexpected character in the port number: '" + std::string(&port[i]) + "'.");
	};

	int converted = std::atoi(port.c_str());
	if (converted < 0 || converted > 65535)
		throw std::invalid_argument("Port number must be between 0 and 65535 (included).");
	return converted;
};

std::string Client::validatePassword(std::string password) {
	if (password.empty())
		throw std::invalid_argument("Password cannot be empty.");

	for (size_t i = 0; i < password.length(); i++) {
		if (isspace(password[i]))
			throw std::invalid_argument("Password cannot contain a space.");
	};

	return password;
};

void Client::signalHandler(int status) {
	_isRunning = false;
	_exitStatus = 128 + status;
	std::cout << '\n';
	print_colored("[SIGNAL RECEIVED]: The Tester has just received an exit signal, so it will exit :)", CYAN);
};

void Client::setSocketOptions(int socketFd) {
	int opt = 1;
	setsockopt(socketFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	setsockopt(socketFd, SOL_SOCKET, SO_KEEPALIVE, &opt, sizeof(opt));
};

pollfd Client::getPollFd(int fd) {
	pollfd pollFd;
	bzero(&pollFd, sizeof(pollFd));
	pollFd.fd = fd;
	pollFd.events = POLLOUT;
	return pollFd;
};

// Parser
void Client::parseOutData(void) {
	std::string& outData = this->getOutData();
	size_t pos = 0;

	while ((pos = outData.find("\n")) != std::string::npos) {
		std::string rawLine = outData.substr(0, pos);

		std::string parsedLine;
		std::string token;
		std::istringstream stream(rawLine);

		while (std::getline(stream, token, ' '))
			parsedLine += token + " ";

		try {
			std::string data = this->execParsedLine(rawLine);
			if (!data.empty()) {
				std::string& inData = this->getInData();
				std::cout << inData << std::endl;
				inData += data + CRLF;
			};
		} catch (std::exception const& err) {
			print_warning(std::string(err.what()));
		};

		outData.erase(0, pos + 1);
	};
};

// Exec
std::string Client::execParsedLine(std::string parsedLine) {
	std::vector<std::string> params = split(parsedLine, ' ');
	std::string result;

	if (!params.size())
		return "";

	std::string cmd = params[0];
	if (cmd[0] != TESTER_PREFIX && this->wantsToSendRawData())
		return parsedLine;
	cmd = cmd.substr(1);
	params.erase(params.begin());

	Command* selectedCommand = this->getCommandByName(cmd);
	if (!selectedCommand)
		print_colored("Cannot find " + cmd + " command, you can do the /help command to get the list of commands.", YELLOW);
	else {
		if ((int)params.size() < selectedCommand->getRequiredParamsNumber())
			print_colored(cmd + " command needs at least " + getStringFromNumber(selectedCommand->getRequiredParamsNumber()) 
														   + " params (given " 
														   + getStringFromNumber(params.size()) + ").", YELLOW);
		else
			result = selectedCommand->execute(this, params);
	};

	return result;
};

// Launcher
void Client::launch(void) {
	this->setFd(socket(AF_INET, SOCK_STREAM, 0));
	int fd = this->getFd();
	if (fd < 0)
		throw std::runtime_error("The tester was not able to create the socket.");

	this->setSocketOptions(fd);

	int port = this->getPort();
	sockaddr_in tester_addr;
	memset(&tester_addr, 0, sizeof(tester_addr));
	tester_addr.sin_family = AF_INET;
	tester_addr.sin_port = htons(port);
	tester_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

	if (connect(fd, (sockaddr*)&tester_addr, sizeof(tester_addr)) < 0) {
		close(fd);
		throw std::runtime_error("Cannot connect the tester to the server.");
	};

	this->setIsRunning(true);
	this->setupSignals();
	this->setupCommands();

	print_colored("\n[TESTER LAUCNHED]: Port: " + getStringFromNumber(port) + " • " + "Password: " + this->getPassword(), PURPLE);
	print_colored("Type /help to get the list commands.", YELLOW);

	std::vector<pollfd>& testerPollFds = this->getPollFds();
	testerPollFds.push_back(this->getPollFd(fd));
	testerPollFds.push_back(this->getPollFd(STDIN_FILENO));

	fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);

	while (this->isRunning()) {
		if (poll(testerPollFds.data(), testerPollFds.size() - 1, -1) < 0) {
			if (!this->getExitStatus()) {
				this->setExitStatus(1);
				this->setIsRunning(false);
				print_error("Error occured when calling the poll function.");
			};
			break;
		};

		for (size_t i = 0; i < testerPollFds.size(); i++) {
			pollfd* it = &testerPollFds[i];
			int pollFd = it->fd;

			if (it->revents & POLLERR) {
				int error = 1;
				socklen_t length = sizeof(error);
				testerPollFds.erase(testerPollFds.begin() + i--);
				if (!getsockopt(pollFd, SOL_SOCKET, SO_ERROR, &error, &length))
					print_warning("Error with the pollFd n°" + getStringFromNumber(pollFd) + ": " + strerror(error));
			} else if (it->revents & POLLOUT && pollFd == fd) {
				if (!this->hasSentBasicTesterData()) {
					std::string logString;
					logString += "PASS " + this->getPassword() + CRLF;
					logString += "NICK " NICK CRLF;
					logString += "USER " USER CRLF;
					send(pollFd, logString.c_str(), logString.size(), MSG_NOSIGNAL);
					this->setSentBasicTesterData(true);
					print_info("Log data sent to the server.");
					print_colored("\n[TESTER INPUT]:", BLUE);
					std::cout << PROMPT << std::flush;
				} else {
					std::string& inData = this->getInData();
					size_t pos = inData.find(CRLF);
					if (pos != std::string::npos) {
						std::string message = inData.substr(0, pos + 2);
						send(pollFd, message.c_str(), message.length(), MSG_NOSIGNAL);
						inData.erase(0, pos + 2);
					};
				};
			} else {
				char buffer[MESSAGE_SIZE];
				bzero(buffer, sizeof(buffer));

				ssize_t readBytes = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
				if (readBytes <= 0)
					break;

				std::string& outData = this->getOutData();
				std::string strBuffer(buffer);

				outData += strBuffer;
				this->parseOutData();
				std::cout << PROMPT << std::flush;
			};
		};
	};
};

void Client::cleanup(void) {
std::vector<pollfd>& pollFds = this->getPollFds();
	for (std::vector<pollfd>::iterator it = pollFds.begin(); it != pollFds.end(); it++)
		close(it->fd);
	pollFds.clear();

	std::map<std::string, Command*>& commands = this->getCommands();
	for (std::map<std::string, Command*>::iterator it = commands.begin(); it != commands.end(); it++) {
		if (it->second) {
			delete it->second;
			it->second = NULL;
		};
	};
	commands.clear();
	close(this->getFd());
};