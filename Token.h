//
// Created by slimsi on 1/14/22.
//

#ifndef CRAFTING_INTERPRETER_TOKEN_H
#define CRAFTING_INTERPRETER_TOKEN_H

#include "TokenType.h"
#include <string>
#include <any>

class Token {
public:
    const TokenType type;
    const std::string lexeme;
    std::any literal;
    const int line;

    Token(TokenType type, std::string lexeme, std::any literal, int line);
    std::string toString();
};


#endif //CRAFTING_INTERPRETER_TOKEN_H
