//
// Created by slimsi on 1/14/22.
//

#ifndef CRAFTING_INTERPRETER_SCANNER_H
#define CRAFTING_INTERPRETER_SCANNER_H

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

#include "Token.h"

class Scanner {
    int start = 0;
    int current = 0;
    int line = 0;
    const std::string source;

    static std::unordered_map<std::string, TokenType> keywords;
    std::vector<std::shared_ptr<Token>> tokens;

    bool isAtEnd();
    void scanToken();
    char advance();
    void addToken(TokenType type);
    void addToken(TokenType type, const std::any& literal);
    bool match(char expected);
    char peek();
    void string();
    bool isDigit(char c);
    void number();
    char peekNext();
    void identifier();
    void comment();

public:
    Scanner(std::string source) : source(std::move(source)) {}

    std::vector<std::shared_ptr<Token>>& scanTokens();
};


#endif //CRAFTING_INTERPRETER_SCANNER_H
