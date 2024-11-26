#pragma once
#ifndef FT_IRCTESTER_HPP
# define FT_IRCTESTER_HPP

// Includes
# include <string>
# include <iostream>
# include <fstream>
# include <sstream>
# include <ctime>
# include <cstring>
# include <stdlib.h>
# include <map>
# include <vector>
# include <poll.h>
# include <ifaddrs.h>
# include <arpa/inet.h>
# include <signal.h>
# include <fcntl.h>

// Client
# include "Client.hpp"

// Commands
# include "Help.hpp"
# include "SendAsPrivmsg.hpp"
# include "SendAsRaw.hpp"
# include "SendFAsPrivmsg.hpp"
# include "SendFAsRaw.hpp"
# include "ToggleRaw.hpp"

// Utils
// print_utils.cpp
std::string getFormattedTime(time_t _time);
std::string getStringFromNumber(int number);
void 		print_logo(void);
void 		print_colored(std::string message, std::string color);
void		print_success(std::string success);
void		print_info(std::string info);
void 		print_warning(std::string warning);
void 		print_error(std::string error);

// string_utils.cpp
std::vector<std::string> split(std::string const& str, char delimiter);

// Colors 
# define RED "\e[31m"
# define GREEN "\e[32m"
# define YELLOW "\e[33m"
# define BLUE "\e[34m"
# define PURPLE "\e[35m"
# define CYAN "\e[36m"
# define WHITE "\e[0m"
# define END_COLOR "\e[0m"
# define BOLD "\e[1m"

// Defines
# define NICK "irctester"
# define USER "ft_irctester 0 0 0 :The almighty tester"
# define CRLF "\r\n"
# define MESSAGE_SIZE 1024
# define PROMPT (BOLD PURPLE "TESTER> " END_COLOR)
# define TESTER_PREFIX '/'

#endif