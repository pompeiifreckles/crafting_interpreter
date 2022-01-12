//
// Created by slimsi on 1/12/22.
//

#include "Lox.h"
#include <fstream>
#include <memory>
#include <iostream>

void Lox::runFile(std::string path) {
    std::ifstream ifs (path);

    if (!ifs)
        throw std::runtime_error("Bad File Provided");

    ifs.seekg(0, std::ios::end);
    ssize_t size = ifs.tellg();
    ifs.seekg(0, std::ios::beg);

    auto bytes = std::make_unique<char[]>(64);
    ifs.read(bytes.get(), size);

//    run(bytes);
}

void Lox::runPrompt() {
    while (true) {
        std::cout << "> ";
        std::string line;

        if (line == std::string::npos) break;
    }
}