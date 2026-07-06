#pragma once

#include <fstream>
#include <string>

class Log{

    private:

        std::string home_dir;
        std::ofstream file;
        const std::string folder = "appmanager/Logs/";

        std::string getTime();
        std::string getFileName();

    public:

        Log();
        ~Log();

        void success(const std::string& message);
        void error(const std::string& message);
        void command(const std::string& message);

};