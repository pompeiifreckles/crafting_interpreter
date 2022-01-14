//
// Created by slimsi on 1/12/22.
//

#include "Lox.h"
#include <iostream>
#include <fstream>
#include <memory>


bool Lox::hadError = false;

void Lox::run(std::string source) {
    std::cout << source << std::endl;

    // auto tokens = scanner->scanTokens();
    // for (auto token : tokens) {
    //      std::cout << token << std::endl;
    // }
}

void Lox::runFile(const std::string& path) {
    std::ifstream ifs (path);

    if (!ifs)
        throw std::runtime_error("Bad File Provided");

    ifs.seekg(0, std::ios::end);
    ssize_t size = ifs.tellg();
    ifs.seekg(0, std::ios::beg);

    auto bytes = std::make_unique<char[]>(size);
    ifs.read(bytes.get(), size);
    ifs.close();

    run(bytes.get());
}

void Lox::runPrompt() {
    while (true) {
        std::cout << "> ";
        std::string line;

        if (getline(std::cin, line).eof())  break;

        run(line);
        hadError = false;
    }
}