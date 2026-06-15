#include "Log.h"

#include <string>
#include <filesystem>
#include <chrono>   //time
#include <sstream>  //string builder
#include <iomanip>  //formater
#include <stdexcept>

Log::Log() {

    std::filesystem::create_directories(folder);

    const std::string filePath = getFileName();

    file.open(filePath, std::ios::app);

    if (!file.is_open()) {

        throw std::runtime_error("Failed to open log file :" + filePath);

    }

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



}

void Log::info(const std::string &message) {

    file << "[" << getTime() << "]" << ">>" << "[ℹ]" << ">>" << message << std::endl;

}

void Log::success(const std::string &message) {

    file << "[" << getTime() << "]" << ">>" << "[✔]" << ">>" << message << std::endl;

}

void Log::error(const std::string &message) {

    file << "[" << getTime() << "]" << ">>" << "[✖]" << ">>" << message << std::endl;

}

void Log::command(const std::string &message) {

    file << "[" << getTime() << "]" << ">>" << "[COMMAND]" << ">>" << message << std::endl;

}
