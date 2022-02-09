//
// Created by slimsi on 1/12/22.
//

#ifndef CRAFTING_INTERPRETER_LOX_H
#define CRAFTING_INTERPRETER_LOX_H

#include <memory>
#include <string>

#include "Token.h"

class Lox {
    static bool hadError;

    static void run(const std::string& source);
    static void report(int line, std::string where, std::string message);
public:
    static void runFile(const std::string& path);
    static void runPrompt();
    static void error(int line, std::string message);
    static void error(std::shared_ptr<Token> token, std::string message);
};


#endif //CRAFTING_INTERPRETER_LOX_H
