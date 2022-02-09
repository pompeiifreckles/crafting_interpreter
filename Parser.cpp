#include <vector>
#include <memory>
#include <initializer_list>

#include "Lox.h"
#include "Expr.h"
#include "Token.h"
#include "TokenType.h"
#include "Parser.h"

template<class T>
std::shared_ptr<Expr<T>> Parser<T>::expression() {
	return equality();
}

template<class T>
std::shared_ptr<Expr<T>> Parser<T>::equality() {
	std::shared_ptr<Expr<T>> expr = comparision();

	while (match( {TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL} )) {
		std::shared_ptr<Token> op = previous();
		std::shared_ptr<Expr<T>> right = comparision();
		expr = std::make_shared<Binary<T>>(expr, op, right);
	}

	return expr;
}

template<class T>
std::shared_ptr<Expr<T>> Parser<T>::comparision() {
	std::shared_ptr<Expr<T>> expr = term();

	while (match( {TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESS, TokenType::LESS_EQUAL} )) {
		std::shared_ptr<Token> op = previous();
		std::shared_ptr<Expr<T>> right = term();
		expr = std::make_shared<Binary<T>>(expr, op, right);
	}

	return expr;
}

template<class T>
std::shared_ptr<Expr<T>> Parser<T>::term() {
	std::shared_ptr<Expr<T>> expr = factor();

	while (match( {TokenType::MINUS, TokenType::PLUS} )) {
		std::shared_ptr<Token> op = previous();
		std::shared_ptr<Expr<T>> right = factor();
		expr = std::make_shared<Binary<T>>(expr, op, right);
	}

	return expr;
}

template<class T>
std::shared_ptr<Expr<T>> Parser<T>::factor() {
	std::shared_ptr<Expr<T>> expr = unary();
	while (match( {TokenType::SLASH, TokenType::STAR} )) {
		std::shared_ptr<Token> op = previous();
		std::shared_ptr<Expr<T>> right = unary();
		expr = std::make_shared<Binary<T>>(expr, op, right);
	}

	return expr;
}

template<class T>
std::shared_ptr<Expr<T>> Parser<T>::unary() {
	if (match( {TokenType::BANG, TokenType::MINUS} )) {
		std::shared_ptr<Token> op = previous();
		std::shared_ptr<Expr<T>> right = unary();
		return std::make_shared<Unary<T>>(op, right);
	}

	return primary();
}

template <class T>
std::shared_ptr<Expr<T>> Parser<T>::primary() {
	if (match( {TokenType::FALSE} )) return std::make_shared<Literal<T>>(std::make_shared<any>(false));
	if (match( {TokenType::TRUE} )) return std::make_shared<Literal<T>>(std::make_shared<any>(true));
	if (match( {TokenType::NIL} )) return std::make_shared<Literal<T>>(std::make_shared<any>(nullptr));

	if (match( {TokenType::NUMBER, TokenType::STRING} )) {
		return std::make_shared<Literal<T>>(std::make_shared<any>(previous()->literal));
	}

	if (match( {TokenType::LEFT_PAREN} )) {
		std::shared_ptr<Expr<T>> expr = expression();
		consume(TokenType::RIGHT_PAREN, "Expect ')' after expression.");
		return std::make_shared<Grouping<T>>(expr);
	}

	throw error(peek(), "Expect expression.");
}

template<class T>
std::shared_ptr<Token> Parser<T>::consume(TokenType type, std::string message) {
	if (check(type)) return advance();

	throw error(peek(), message);
}


template<class T>
bool Parser<T>::match(std::initializer_list<TokenType> types) {
	for (auto type : types) {
		if (check(type)) {
			advance();
			return true;
		}
	}

	return false;
}

template<class T>
bool Parser<T>::check(TokenType type) {
	if (isAtEnd()) return false;
	return peek()->type == type;
}

template<class T>
std::shared_ptr<Token> Parser<T>::advance() {
	if (!isAtEnd()) current++;
	return previous();
}

template<class T>
bool Parser<T>::isAtEnd() {
	return peek()->type == TokenType::_EOF;
}

template<class T>
std::shared_ptr<Token> Parser<T>::peek() {
	return tokens[current];
}

template<class T>
std::shared_ptr<Token> Parser<T>::previous() {
	return tokens[current - 1];
}

template<class T>
std::shared_ptr<ParseError> Parser<T>::error(std::shared_ptr<Token> token, std::string message) {
	Lox::error(token, message);
	return std::make_shared<ParseError>();
}

template<class T>
void Parser<T>::synchronize() {
	advance();

	while (!isAtEnd()) {
		if (previous()->type == TokenType::SEMICOLON) return;
		
		switch (peek()->type) {
			case TokenType::CLASS:
			case TokenType::FUN:
			case TokenType::VAR:
			case TokenType::FOR:
			case TokenType::IF:
			case TokenType::WHILE:
			case TokenType::PRINT:
			case TokenType::RETURN:
				return;
		}
		
		advance();
	}
}

template<class T>
Parser<T>::Parser(std::vector<std::shared_ptr<Token>> tokens)
	: tokens(tokens) {}

template<class T>
std::shared_ptr<Expr<T>> Parser<T>::parse() {
	try {
		return expression();
	} catch (std::shared_ptr<ParseError> error) {
		return nullptr;
	}
}
