//
// Created by slimsi on 1/12/22.
//

#include "Lox.h"
#include "Scanner.h"
#include <iostream>
#include <fstream>
#include <memory>


bool Lox::hadError = false;

void Lox::run(const std::string& source) {
//    std::cout << source << std::endl;

    std::unique_ptr<Scanner> scanner = std::make_unique<Scanner>(source);
    auto tokens = scanner->scanTokens();

    for (auto& token : tokens) {
      std::cout << token->toString() << std::endl;
    }
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
    if (hadError) exit(65);
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

void Lox::error(int line, const std::string message) {
    report(line, "", message);
}

void Lox::report(int line, std::string where, std::string message) {
    std::cerr << "[line " + std::to_string(line) + "] Error" + where +
    ": " + message << std::endl;
    hadError = true;
}
