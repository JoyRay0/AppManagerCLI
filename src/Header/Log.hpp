#pragma once

#include <fstream>
#include <string>

class Log{

    private:

        std::ofstream file;
        std::string folder = "appmanager/Logs/";

        std::string getTime();
        std::string getFileName();


    public:

        Log();
        ~Log();

        void info(const std::string& message);
        void success(const std::string& message);
        void error(const std::string& message);
        void command(const std::string& message);


};