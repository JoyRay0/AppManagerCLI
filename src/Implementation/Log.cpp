#include "Log.hpp"

#include <string>
#include <filesystem>
#include <chrono>   //time
#include <sstream>  //string builder
#include <iomanip>  //formater
#include <stdexcept>

Log::Log() {

    home_dir = std::getenv("HOME") ? std::getenv("HOME") : "";

    std::filesystem::create_directories(home_dir +  "/" + folder);

    const std::string filePath = getFileName();

    file.open(home_dir + "/" +folder + filePath, std::ios::app);

    if (!file.is_open()) {

        throw std::runtime_error("Failed to open log file :" + filePath);

    }

    file.close();

}

Log::~Log() {

    if (file.is_open()) file.close();

}

std::string Log::getTime() {

    const auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);

    std::stringstream ss;

    ss << std::put_time(std::localtime(&t), "%Y-%m-%d %H:%M:%S");
    
    return ss.str();
}

std::string Log::getFileName() {

    const auto now = std::chrono::system_clock::now();

    std::time_t t = std::chrono::system_clock::to_time_t(now);

    std::stringstream ss;

    ss << std::put_time(std::localtime(&t), "%Y-%m") << ".txt";

    return ss.str();

}


void Log::success(const std::string &message) {

    file.open(home_dir + "/" + folder + getFileName(), std::ios::app);

    file << "[" << getTime() << "]" << " >> " << "[✔]" << " >> " << message << "\n";

    file.close();

}

void Log::error(const std::string &message) {

    file.open(home_dir + "/" + folder + getFileName(), std::ios::app);

    file << "[" << getTime() << "]" << " >> " << "[✖]" << " >> " << message << "\n";

    file.close();

}

void Log::command(const std::string &message) {

    file.open(home_dir + "/" + folder + getFileName(), std::ios::app);

    file << "[" << getTime() << "]" << " >> " << "[COMMAND]" << " >> " << message << "\n";

    file.close();

}
