#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>

int main() {

    std::ofstream headerFile;
    std::ofstream implFile;

    std::string fileName;
    std::string header = "src/Header/";
    std::string implementation = "src/Implementation/";

    std::cout << "Enter your file name:" << std::endl;
    std::cout << "=>";
    getline(std::cin, fileName);

    if (fileName.empty()) {

        std::cout << "Empty file name" << std::endl;
        return 1;

    }

    if (std::filesystem::exists(header + fileName + ".h") ||
        std::filesystem::exists(implementation + fileName + ".cpp")) {

        std::cout << "File already exists" << std::endl;
        return 1;

    }

    headerFile.open(header + fileName + ".h", std::ios::app);
    implFile.open(implementation + fileName + ".cpp", std::ios::app);

    if (!headerFile.is_open() || !implFile.is_open()) {

        std::cout << "Failed to create file!" << std::endl;
        return 1;

    }

    //header
    headerFile << "#pragma once" << std::endl;
    headerFile << "#include " << "<string>" << std::endl;
    headerFile << "#include " << "<fstream>" << std::endl;
    headerFile << "\n\n" << std::endl;
    headerFile << "class " + fileName + "{\n\n};" << std::endl;

    //implementation
    implFile << "#include \"" << fileName << ".h\"" << std::endl;
    implFile << "#include " << "<string>" << std::endl;
    implFile << "#include " << "<filesystem>" << std::endl;

    std::cout << "File created successfully!" << std::endl;

    headerFile.close();
    implFile.close();

    return 0;

}//fun end
