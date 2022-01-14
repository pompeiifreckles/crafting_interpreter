#include <iostream>
#include "Lox.h"

int main(int argc, char *argv[])
try {
    if (argc > 2) {
        std::cout << "Usage: clox [script]" << std::endl;
        exit(64);
    } else if (argc == 2) {
        Lox::runFile(argv[1]);
    } else {
        Lox::runPrompt();
    }
}
catch (std::exception& e) {
    std::cerr << "Ouch! This hurts: " << e.what() << std::endl;
    exit(1);
}