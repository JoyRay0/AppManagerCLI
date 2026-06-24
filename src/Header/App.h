#pragma once

#include "Log.h"

#include <string>
#include <fstream>

class App{

    private:

        Log log;

        std::ofstream write_json_file;
        std::ifstream read_json_file;

        std::string json_file_name = "app_commands.json";
        std::string appmanager_folder = "appmanager/";
        std::string home_dir;

        std::string info = "[ℹ] ";
        std::string success = "[✔] ";
        std::string error = "[✖] ";

        void output(const std::string& id, const std::string& title);
        void print(const std::string& message);
        void help_print(const std::string& cmd_name, const std::string& description);
        void empty_app_info();
        bool check_id(const std::string& id);


    public:
        App();
        ~App();

        void home();
        void add_command();
        void run_command(const std::string& id);
        void delete_command(const std::string& id);
        void reset_command();
        void log_clear(const std::string& text);
        void list();
        void version(const std::string& version);
        void help();

};
