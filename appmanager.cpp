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

    return ARGV::INVALID;

}

int main(const int argc, const char* argv[]) {

    Log logeer;
    App app;
    auto cmd = ARGV::HOME;

    if (argc > 1) cmd = string_to_argv(argv[1]);

    switch (cmd) {

        case ARGV::HOME:

            app.home();

            break;

        case ARGV::ADD:

            app.add_command();

            break;

        case ARGV::RUN:

            app.run_command(argv[2]);

            break;

        case ARGV::DELETE:

            app.delete_command(argv[2]);

            break;

        case ARGV::RESET:

            app.reset_command();

            break;

        case ARGV::LIST:

            app.list();

            break;

        case ARGV::LOG:

            app.log_clear(argv[2]);

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