#include "App.h"

#include <iostream>
#include <string>
#include <filesystem>
#include <vector>
#include <cstdlib>
#include "json.hpp"

using json = nlohmann::json;

App::App() {

    //======================================
    // Get home directories
    //======================================

    home_dir = std::getenv("HOME") ? std::getenv("HOME") : "";

    //===================================
    // Creating folders
    //===================================

    std::filesystem::create_directories(home_dir + appmanager_folder);
    std::filesystem::create_directories(home_dir + appmanager_folder + "Logs/");

    if (!write_json_file.is_open()) {

        write_json_file.open(home_dir + appmanager_folder + json_file_name);
        write_json_file << "[]" << std::endl;

    }

    if (write_json_file.is_open()) write_json_file.close();

}

App::~App() {

    if (write_json_file.is_open()) write_json_file.close();

    if (read_json_file.is_open()) read_json_file.close();

}

void App::home() {

    std::string user_choice;
    std::string json_content = "";
    json app_data;
    bool is_valid_digit = false;
    bool is_app_id_found = false;
    std::string app_title = "";
    std::vector<std::string> app_commands;

    read_json_file.open(home_dir + appmanager_folder + json_file_name);

    getline(read_json_file, json_content);

    if (json_content == "[]") {

        log.error("No app data found");
        empty_app_info();
        return;

    }

    read_json_file >> app_data;

    read_json_file.close();

    for (auto& data : app_data) {

        output(data["app_id"], data["app_title"]);

    }

    std::cout << "=>";
    getline(std::cin, user_choice);

    for (const char number : user_choice) {

        if (!isdigit(number)) {

            is_valid_digit = false;
            break;

        }else {

            is_valid_digit = true;

        }

    }

    if (!is_valid_digit) {

        log.error("[" + user_choice + "]" + " Invalid app id");
        print(error + "Invalid app id");
        return;

    }

    for (auto& data : app_data) {

        if (data["app_id"] == user_choice) {

            is_app_id_found = true;
            app_title = data["app_title"];

            for (auto& cmd : data["app_command"]) {

                app_commands.push_back(cmd);

            }

           break;

        }

    }

    if (!is_app_id_found) {

        log.error("[" + user_choice + "]" + " App id not found");
        print(error + "Invalid id");
        return;

    }

    std::system("clear");

    std::cout << "=========================================" << std::endl;
    std::cout << "Launching " + app_title << std::endl;
    std::cout << "=========================================" << std::endl;

    for (const std::string& command : app_commands) {

        std::system(command.c_str());

    }

}

void App::run_command(const std::string& id) {

    //=================================
    // Initial value
    //=================================

    std::string json_content;
    json app_data;
    bool is_app_id_found = false;
    std::string app_id = "";
    std::vector<std::string> app_commands;

    read_json_file.open(home_dir + appmanager_folder + json_file_name);

    getline(read_json_file, json_content);

    if (json_content == "[]") {

        log.error("Empty app list");
        empty_app_info();
        return;

    }

    read_json_file >> app_data;

    read_json_file.close();

    for (auto& data : app_data) {

        if (data["app_id"] == id) {

            is_app_id_found = true;
            app_id = data["app_id"];

            for (std::string command : app_commands) {

                app_commands.push_back(command);

            }

            break;

        }

    }

    if (!is_app_id_found) {

        log.error("[" + app_id + "]" + " App id not found");
        print(error + "Invalid id");
        return;

    }

    for (const std::string& command : app_commands) {

        std::system(command.c_str());

    }


}

void App::add_command() {

    std::vector<std::string> menu = {"Single command", "Multiple command"};

    int selected = 0;

    while (true) {

        for (int i = 0; i < menu.size(); i++) {

            std::cout << "→" << " " << menu[i] << std::endl;
            std::cout << " " << " " << menu[i] << std::endl;


        }

    }//loop


}

void App::delete_command() {


}

void App::reset_command() {

    std::string json_content;
    std::string user_confirm;
    bool is_confirmed = false;

    read_json_file.open(home_dir + appmanager_folder + json_file_name);

    getline(read_json_file, json_content);

    read_json_file.close();

    if (json_content == "[]") {

        log.error("Empty json file can not reset");
        empty_app_info();
        return;

    }

    std::cout << "Are you sure you want reset all [Y/n] : ";
    getline(std::cin, user_confirm);

    if (user_confirm == "Y" || user_confirm == "y") {

        is_confirmed = true;

    }else {

        is_confirmed = false;

    }

    if (is_confirmed) {

        write_json_file.open(home_dir + appmanager_folder + json_file_name);

        write_json_file << "[]" << std::endl;

        write_json_file.close();

        log.success("All app commands cleared");
        print(success + "Reset successfully");

    }else {

        log.error("Invalid text can not reset");
        print(error + "Invalid text");

    }

}

void App::list() {

}

void App::log_clear(const std::string& text) {

    std::string user_confirm;
    bool is_confirmed = false;

    if (text != "clear") {

        log.error("Wrong command for clear all logs");
        print(info + "Use : appmanager log clear");

    }

    std::cout << "Are you sure ? [Y/n] : ";
    getline(std::cin, user_confirm);

    if (user_confirm == "Y" || user_confirm == "y") {

        is_confirmed = true;

    } else {

        is_confirmed = false;

    }

    if (is_confirmed) {

        std::filesystem::remove_all(home_dir + appmanager_folder + "/Logs");

        log.success("All log files deleted successfully");
        print(success + "Logs deleted successfully");

    }else {

        log.error("Logs delete failed");
        print(error + "Logs delete failed");

    }

}

void App::version(const std::string& version) {

    std::cout << "appmanager version " + version << std::endl;

}

void App::help() {

    std::cout << "Usage:" << std::endl;
    std::cout << "   appmanager" <<std::endl;
    std::cout << "   appmanager <command> [options]" <<std::endl;

    std::cout << " " << std::endl;
    std::cout << "Common AppManager commands" << std::endl;
    std::cout << " " << std::endl;

    help_print("add", "Add a new application to the appmanager");
    help_print("run <id>", "Launch an installed application directly using its assigned ID");
    help_print("delete", "Safely remove an application from the appmanager");
    help_print("reset", "Hard-reset the entire the application");
    help_print("list", "Display the comprehensive list of available commands and titles");
    help_print("log clear", "Removes all log files generated by AppManager and resets the log directory");


}

void App::output(const std::string& id, const std::string& title) {

    const std::string bold_text = "\033[1m";
    const std::string green_color = "\033[32m";
    const std::string reset = "\033[0m";

    std::cout << "[" << green_color + bold_text + id + reset << "]"
    << " " << green_color + bold_text + title + reset << std::endl;

}

void App::print(const std::string& message) {

    std::cout << "\n" << std::endl;
    std::cout << message << std::endl;

}

void App::help_print(const std::string &cmd_name, const std::string &description) {

    std::cout << std::left << std::setw(12) << cmd_name << " - " << description << std::endl;

}

void App::empty_app_info() {

    std::cout << "> Add your first app:" << std::endl;
    std::cout << "   appmanager add" << std::endl;

}

