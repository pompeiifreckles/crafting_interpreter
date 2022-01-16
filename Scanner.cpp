//
// Created by slimsi on 1/14/22.
//

#include "Scanner.h"
#include "Lox.h"

std::unordered_map<std::string, TokenType> Scanner::keywords {
        {"and", TokenType::AND},
        {"class", TokenType::CLASS},
        {"else", TokenType::ELSE},
        {"false", TokenType::FALSE},
        {"for", TokenType::FOR},
        {"fun", TokenType::FUN},
        {"if", TokenType::IF},
        {"nil", TokenType::NIL},
        {"or", TokenType::OR},
        {"print", TokenType::PRINT},
        {"return", TokenType::RETURN},
        {"super", TokenType::SUPER},
        {"this", TokenType::THIS},
        {"true", TokenType::TRUE},
        {"var", TokenType::VAR},
        {"while", TokenType::WHILE}
};

std::vector<std::shared_ptr<Token>>& Scanner::scanTokens() {
    while (!isAtEnd()) {
        start = current;
        scanToken();
    }

    tokens.push_back(std::make_shared<Token>(TokenType::_EOF, "", nullptr, line));
    return tokens;
}

bool Scanner::isAtEnd() {
    return current >= source.length();
}

void Scanner::scanToken() {
    char c = advance();
    switch (c) {
        case '(': addToken(TokenType::LEFT_PAREN); break;
        case ')': addToken(TokenType::RIGHT_PAREN); break;
        case '{': addToken(TokenType::LEFT_BRACE); break;
        case '}': addToken(TokenType::RIGHT_BRACE); break;
        case ',': addToken(TokenType::COMMA); break;
        case '.': addToken(TokenType::DOT); break;
        case '-': addToken(TokenType::MINUS); break;
        case '+': addToken(TokenType::PLUS); break;
        case ';': addToken(TokenType::SEMICOLON); break;
        case '*':
            if (match('/')) {
                Lox::error(line, "Unterminated comment.");
                break;
            }
            addToken(TokenType::STAR);
            break;
        case '!':
            addToken(match('=') ? TokenType::BANG_EQUAL : TokenType::BANG);
            break;
        case '=':
            addToken(match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL);
            break;
        case '<':
            addToken(match('=') ? TokenType::LESS_EQUAL : TokenType::LESS);
            break;
        case '>':
            addToken(match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER);
            break;
        case '/':
            if (match('/')) {
                // A comment goes until the end of the line.
                while (peek() != '\n' && !isAtEnd()) advance();
            } else if (match('*')) {
                comment();
            } else {
                addToken(TokenType::SLASH);
            }
            break;
        case ' ':
        case '\r':
        case '\t':
            // Ignore whitespace.
            break;

        case '\n':
            line++;
            break;
        case '"': Scanner::string(); break;

//        case 'o':                         // not Maximal Munch, "orchid" -> "or"(OR) + "chid"(IDENTIFIER)
//            if (match('r')) {
//                addToken(TokenType::OR);
//            }
//            break;

        default:
            if (isDigit(c)) {
                number();
            } else if (std::isalpha(c) || c == '_') {
                identifier();
            } else {
                Lox::error(line, "Unexpected character.");
            }
            break;
    }
}

char Scanner::advance() {
    return source[current++];
}

void Scanner::addToken(TokenType type) {
    addToken(type, nullptr);
}

void Scanner::addToken(TokenType type, const std::any& literal) {
    std::string text = source.substr(start, current - start);
    tokens.push_back(std::make_shared<Token>(type, text, literal, line));
}

bool Scanner::match(char expected) {
    if (isAtEnd()) return false;
    if (source[current] != expected) return false;

    current += 1;
    return true;
}

char Scanner::peek() {
    if (isAtEnd()) return '\0';
    return source[current];
}

void Scanner::string() {
    while (peek() != '"' && !isAtEnd()) {
        if (peek() == '\n') line++;
        advance();
    }

    if (isAtEnd()) {
        Lox::error(line, "Unterminated string.");
        return;
    }

    advance();

    std::string value = source.substr(start + 1, current - 2 - start);
    addToken(TokenType::STRING, value);
}

bool Scanner::isDigit(char c) {
    return c >= '0' && c <= '9';
}

void Scanner::number() {
    while (isDigit(peek())) advance();

    // Look up the fractional part
    if (peek() == '.' && isDigit(peekNext())) {
        // Consume the "."
        advance();

        while (isDigit(peek())) advance();
    }

    addToken(TokenType::NUMBER, new double(std::stod(source.substr(start, current - start))));
}

char Scanner::peekNext() {
    if (current + 1 >= source.length()) return '\0';
    return source[current + 1];
}

void Scanner::identifier() {
    while (std::isalnum(peek()) || peek() == '_') advance();

    std::string text = source.substr(start, current - start);

    TokenType type;
    if (auto it = keywords.find(text); it == end(keywords)) {
        type = TokenType::IDENTIFIER;
    } else {
        type = it->second;
    }

    addToken(type);
}

void Scanner::comment() {
    int count {1};

    while (count != 0 && !isAtEnd()) {
        if (peek() == '\n') {
            line += 1;
        } else if (peek() == '*' && peekNext() == '/') {
            count -= 1;
            advance();
        } else if (peek() == '/' && peekNext() == '*') {
            count += 1;
            advance();
        }
        advance();
    }

    if (count != 0 && isAtEnd()) {
        Lox::error(line, "Unterminated comment.");
    }
}

