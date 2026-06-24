#include "App.h"

#include <iostream>
#include <string>
#include <filesystem>
#include <vector>
#include <cstdlib>

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
    bool is_valid_digit = false;
    bool is_app_id_found = false;
    std::string app_title = "";
    std::vector<std::string> app_commands;

    json app = json::parse(json_file_name);

    if (!app.is_array() && app.empty()) {

        app = json::array();
        log.error("No app data found");
        empty_app_info();
        return;

    }


    for (auto& data : app) {

        output(data["app_id"].get<std::string>(), data["app_title"].get<std::string>());

    }

    std::cout << ">";
    getline(std::cin, user_choice);

    if (!check_id(user_choice)) {

        log.error("Empty app id found");
        print(error + "Invalid id");
        return;
    }

    for (auto& data : app) {

        if (data["app_id"].get<std::string>() == user_choice) {

            is_app_id_found = true;
            app_title = data["app_title"].get<std::string>();

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
    bool is_app_id_found = false;
    std::string app_id = "";
    std::string app_title = "";
    std::vector<std::string> app_commands;

    json app = json::parse(json_file_name);


    if (!check_id(app_id)) {

        log.error("Empty app id found");
        print(error + "Invalid id");
        return;
    }

    //=========================================
    // Checking empty JSON
    //=========================================

    if (app.is_array() && app.empty()) {

        log.error("Empty app list");
        empty_app_info();
        return;

    }

    //=================================
    // Fetching JSON data
    //=================================

    for (auto& data : app) {

        if (data["app_id"].get<std::string>() == id) {

            is_app_id_found = true;
            app_title = data["app_title"];

            for (std::string command : data["app_command"]) {

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

    std::system("clear");

    std::cout << "======================================" << std::endl;
    std::cout << "Launching " + app_title << std::endl;
    std::cout << "======================================" << std::endl;

    for (const std::string& command : app_commands) {

        std::system(command.c_str());

    }

}

void App::add_command() {

    //=====================
    // Initialize variable
    //=====================

    std::string app_id = "";
    std::string app_title = "";
    std::string app_command = "";
    std::vector<std::string> commands;
    std::string tem_command_data = "";
    bool is_inside = false;
    bool is_duplicate_id = false;

    json app;   //Creating object
    json root = json::parse(json_file_name); //Opening json file


    //==========================================
    // User input for save id, title, commands
    //==========================================

    //app id
    std::cout << "Id :" << std::endl;
    std::cout << ">";
    getline(std::cin, app_id);

    if (!check_id(app_id)) {

        log.error("Empty app id found");
        print(error + "Invalid id");
        return;
    }

    //app title
    std::cout << "Title :" << std::endl;
    std::cout << ">";
    getline(std::cin, app_title);

    if (app_title.empty()) {

        log.error("Empty app title found");
        print(error + "Invalid title");
        return;
    }

    //app command
    std::cout << R"(Commands (use double quotes and spaces to separate commands. e.g: "A" "B" "C" "D 'd'"):)" << std::endl;
    std::cout << ">";
    getline(std::cin, app_command);

    if (app_command.empty()) {

        log.error("Empty commands found");
        print(error + "Invalid commands");
        return;
    }

    //=============================
    // Separating commands
    //=============================
    
    for (const char c_command : app_command) {

        if (c_command == '"') {

            if (is_inside) {

                commands.push_back(tem_command_data);
                tem_command_data = "";

            }

            is_inside = !is_inside;

        }else if (is_inside) {

            tem_command_data = tem_command_data + c_command;

        }

    }//loop

    if (!root.is_array()) {

        root = json::array();

    }

    //==================================
    // Checking duplicate id
    //==================================

    for (auto& item : root) {

        if (item["app_id"].get<std::string>() == app_id) {

            is_duplicate_id = true;

        }

    }

    if (is_duplicate_id) {

        log.error("Duplicate id found");
        print(error + "Duplicate id found");
        return;

    }

    //============================
    // Creating JSON object
    //============================

    app["app_id"] = app_id;
    app["app_title"] = app_title;
    app["app_command"] = commands;

    root.push_back(app);

    log.success("Application saved successfully");
    print(success + "Application saved successfully");

}

void App::delete_command(const std::string& id) {

    //=================================
    // Initialized variable
    //=================================

    json app = json::parse(json_file_name);

    std::string app_id = "";
    bool is_app_id_found = false;

    if (!check_id(id)) {

        log.error("Empty id found");
        print(error + "Invalid id");
        return;

    }

    //========================================
    // Checking app id in JSON file
    //========================================

    for (auto& item : app) {

        if (item["app_id"].get<std::string>() == id) {

            is_app_id_found = true;
            break;

        }else {

            is_app_id_found = false;

        }

    }

    if (!is_app_id_found) {

        log.error("[" + app_id + "]" + "Id not found");
        print(error + "Id not found");
        return;

    }

    //============================================
    // Removing object from JSON array via id
    //============================================

    app.erase(id);


}

void App::reset_command() {

    //==================================
    // Initialize variable
    //==================================

    std::string user_confirm;
    bool is_confirmed = false;
    json app = json::parse(json_file_name);


    if (!app.is_array() && app.empty()) {

        app = json::array();
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

        app.clear();

        log.success("All app commands cleared");
        print(success + "Reset successfully");

    }else {

        log.error("Invalid text can not reset");
        print(error + "Invalid text");

    }

}

void App::list() {

    //=============================
    // Initialize variable
    //=============================

    json app = json::parse(json_file_name);

    if (!app.is_array() && app.empty()) {

        app = json::array();
        log.error("Empty app list found");
        empty_app_info();
        return;

    }

    table.add_row({"No", "Title", "Command"});

    for (const auto& data : app) {

        std::string command;

        for (const auto& cmd : data["app_command"]) {

            if (!command.empty()) {

                command += ", ";

            }

            command += cmd;

        }

        table.add_row({
            data["app_id"].get<std::string>(),
            data["app_title"].get<std::string>(),
            command});

    }

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

bool App::check_id(const std::string& id) {

    bool is_valid_id = false;

    if (id.empty()) is_valid_id = false;

    for (const char number : id) {

        if (!isdigit(number)) {

            is_valid_id = false;
            break;

        }else {

            is_valid_id = true;

        }

    }

    return is_valid_id;

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

