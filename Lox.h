//
// Created by slimsi on 1/12/22.
//

#ifndef CRAFTING_INTERPRETER_LOX_H
#define CRAFTING_INTERPRETER_LOX_H

#include <string>

class Lox {
    static bool hadError;

    static void run(std::string source);
public:
    static void runFile(const std::string& path);
    static void runPrompt();
};


#endif //CRAFTING_INTERPRETER_LOX_H
