//
// Created by slimsi on 1/14/22.
//

#include "Token.h"

std::string Token::toString() {
    if (literal.type() == typeid(const char *)) {
        return tokenTypes[int(type)] + " " + lexeme + " " + std::any_cast<const char *>(literal);
    } else if (literal.type() == typeid(std::string)) {
        return tokenTypes[int(type)] + " " + lexeme + " " + std::any_cast<std::string>(literal);
    } else if (literal.type() == typeid(double)) {
        return tokenTypes[int(type)] + " " + lexeme + " " + std::to_string(std::any_cast<double>(literal));
    }
    return tokenTypes[int(type)] + " " + lexeme;
}

Token::Token(TokenType type, std::string lexeme, std::any literal, int line)
        : type(type), lexeme(std::move(lexeme)), literal(std::move(literal)), line(line) {}
