//
// Created by pointerlost on 7/22/25.
//
#include <iostream>
#include <fstream>
#include "FileHandler.h"

namespace core {

    std::string FileHandler::readFile(const std::string &filePath) {
        std::cout << "trying to read file: " << filePath << "\n";
        std::ifstream file(filePath);

        if (!file.is_open()) {
            std::cerr << "File can't be opened: " << filePath << "\n";
            return {};
        }

        file.seekg(0, std::ios::end); // go to end
        const std::streamsize fileSize = file.tellg(); // get size
        file.seekg(0, std::ios::beg); // go back to beginning

        std::string buffer(fileSize, '\0'); // allocate buffer
        if (!file.read(buffer.data(), fileSize)) {
            std::cerr << "Error: Only read " << file.gcount() << " bytes.\n";
            return {};
        }

        return buffer;
    }
}