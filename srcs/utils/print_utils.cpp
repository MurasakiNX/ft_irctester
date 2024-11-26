#include "ft_irctester.hpp"

// String getters
std::string getFormattedTime(time_t _time) {
	char buffer[100];
	tm* localTime = std::localtime(&_time);
	std::strftime(buffer, sizeof(buffer), "[%m/%d/%Y • %H:%M:%S]", localTime);
	return std::string(buffer);
};

std::string getStringFromNumber(int number) {
	std::ostringstream oss;
	oss << number;
	return oss.str();
};

// Printers
void print_logo(void) {
	print_colored("  ______    __            __                        __                            __", CYAN);
    print_colored(" /      \\  /  |          /  |                      /  |                          /  |", CYAN);
    print_colored("/######  |_## |_         ##/   ______    _______  _## |_     ______    _______  _## |_     ______    ______", CYAN);
    print_colored("## |_ ##// ##   |        /  | /      \\  /       |/ ##   |   /      \\  /       |/ ##   |   /      \\  /      \\", CYAN);
    print_colored("##   |   ######/         ## |/######  |/#######/ ######/   /######  |/#######/ ######/   /######  |/######  |", CYAN);
    print_colored("####/      ## | __       ## |## |  ##/ ## |        ## | __ ##    ## |##      \\   ## | __ ##    ## |## |  ##/", CYAN);
    print_colored("## |       ## |/  |      ## |## |      ## \\_____   ## |/  |########/  ######  |  ## |/  |########/ ## |", CYAN);
    print_colored("## |       ##  ##/______ ## |## |      ##       |  ##  ##/ ##       |/     ##/   ##  ##/ ##       |## |", CYAN);
    print_colored("##/         ####//      |##/ ##/        #######/    ####/   #######/ #######/     ####/   #######/ ##/", CYAN);
    print_colored("                 ######/\n", CYAN);
    print_colored("   ======================================= By mel-habi • v1.0 =======================================", PURPLE);
    std::cout << std::endl;
};

void print_colored(std::string message, std::string color) {
	std::cout << BOLD << color
			  << message << END_COLOR << std::endl;
};

void print_success(std::string success) {
	std::cout << BOLD GREEN
			  << getFormattedTime(std::time(NULL))
			  << " • [SUCCESS]: " << success << END_COLOR << std::endl;
};

void print_info(std::string info) {
	std::cout << BOLD CYAN
			  << getFormattedTime(std::time(NULL))
			  << " • [INFO]: " << info << END_COLOR << std::endl;
};

void print_warning(std::string warning) {
	std::cerr << BOLD YELLOW
			  << getFormattedTime(std::time(NULL))
			  << " • [WARNING]: " << warning << END_COLOR << std::endl;
};

void print_error(std::string error) {
	std::cerr << BOLD RED 
			  << getFormattedTime(std::time(NULL)) 
			  << " • [ERROR]: " << error << END_COLOR << std::endl;
};