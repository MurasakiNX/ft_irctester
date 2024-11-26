#include "ft_irctester.hpp"

int main(int argc, char** argv) {
    print_logo();

    if (argc != 3) {
        print_colored("[TESTER ERROR]: Please provide at least 2 arguments, ./irctester [PORT] [PASSWORD]", RED);
        print_colored("[TESTER INFO]: For example: ./irctester 4242 FortyTwo", CYAN);
        return 1;
    };

    std::string port = argv[1];
	std::string password = argv[2];

    try {
        Client client(port, password);
        client.launch();
        client.cleanup();
        print_colored("[TESTER EXITED]: Bye bye!", GREEN);
        return client.getExitStatus();
    } catch (std::exception const& err) {
        print_colored("[TESTER ERROR]: " + std::string(err.what()), RED);
        return 1;
    };

    return 0;
};