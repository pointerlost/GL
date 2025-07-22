//
// Created by pointerlost on 7/22/25.
//
#pragma once
#include <string>

/*
std::ifstream -> input file stream - (read from file)
std::ofstream -> output file stream - (write to file)
std::fstream -> both input and output - (read / write)
*/

namespace core {

    class FileHandler {
    public:
        FileHandler() = default;
        ~FileHandler() = default;

        static std::string readFile(const std::string &filePath);
    };

}



