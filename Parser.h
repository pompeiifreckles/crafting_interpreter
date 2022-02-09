#ifndef CRAFTING_INTERPRETER_PARSER_H
#define CRAFTING_INTERPRETER_PARSER_H

#include <vector>
#include <memory>
#include <initializer_list>

#include "Token.h"
#include "Expr.h"

class ParseError : public std::exception {

};

template<class T>
class Parser {
	std::vector<std::shared_ptr<Token>> tokens; // might make it a ptr
	int current = 0;

	bool match(std::initializer_list<TokenType> types);
	bool check(TokenType type);
	bool isAtEnd();
	std::shared_ptr<Token> advance();
	std::shared_ptr<Token> peek();
	std::shared_ptr<Token> previous();
	std::shared_ptr<Expr<T>> expression();
	std::shared_ptr<Expr<T>> equality();
	std::shared_ptr<Expr<T>> comparision();
	std::shared_ptr<Expr<T>> term();
	std::shared_ptr<Expr<T>> factor();
	std::shared_ptr<Expr<T>> unary();
	std::shared_ptr<Expr<T>> primary();
	std::shared_ptr<Token> consume(TokenType type, std::string message);
	std::shared_ptr<ParseError> error(std::shared_ptr<Token> token, std::string message);

	void synchronize();

	public:
	
	Parser(std::vector<std::shared_ptr<Token>> tokens);
	std::shared_ptr<Expr<T>> parse();

};

template class Parser<std::string>;

#endif
