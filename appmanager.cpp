#include "src/Header/Log.hpp"
#include "src/Header/App.hpp"
#include <iostream>
#include <string>

enum class ARGV {

    HOME,
    ADD,
    DELETE,
    RUN,
    RESET,
    LIST,
    LOG,
    VERSION,
    INVALID

};

ARGV string_to_argv(const std::string& argv_text) {

    if (argv_text == "home") return ARGV::HOME;
    if (argv_text == "add") return ARGV::ADD;
    if (argv_text == "run") return ARGV::RUN;
    if (argv_text == "delete") return ARGV::DELETE;
    if (argv_text == "reset") return ARGV::RESET;
    if (argv_text == "list") return ARGV::LIST;
    if (argv_text == "log") return ARGV::LOG;
    if (argv_text == "version" || argv_text == "-v") return ARGV::VERSION;

    return ARGV::INVALID;

}

int main(const int argc, const char* argv[]) {

    //================================
    // Initialize variable
    //================================

    Log logeer;
    App app;
    auto cmd = ARGV::HOME;
    const std::string APP_VERSION = "1.0.6";

    if (argc > 1) cmd = string_to_argv(argv[1]);

    switch (cmd) {

        case ARGV::HOME:

            app.home();

            break;

        case ARGV::ADD:

            app.add_command();

            break;

        case ARGV::RUN:

            if (argc == 3) {

                app.run_command(argv[2]);

            }else {

                std::cout << "Invalid Command" << std::endl;
                std::cout << "Use : appmanager help" << std::endl;

            }


            break;

        case ARGV::DELETE:

            if (argc == 3) {

                app.delete_command(argv[2]);

            }else {

                std::cout << "Invalid Command" << std::endl;
                std::cout << "Use : appmanager help" << std::endl;

            }

            break;

        case ARGV::RESET:

            app.reset_command();

            break;

        case ARGV::LIST:

            app.list();

            break;

        case ARGV::LOG:

            if (argc == 3) {

                app.log_clear(argv[2]);

            }else {

                std::cout << "Invalid Command" << std::endl;
                std::cout << "Use : appmanager help" << std::endl;

            }

            break;

        case ARGV::VERSION:

            app.version(APP_VERSION);

            break;

        case ARGV::INVALID:

            std::cout << "Invalid Command" << std::endl;
            std::cout << "Use : appmanager help" << std::endl;

            break;

        default:
            break;

    }

    return 0;

}