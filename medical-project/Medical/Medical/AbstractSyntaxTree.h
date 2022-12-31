#pragma once
#include <string>
#include <vector>

enum TokenType
{
	LEFTPAREN,
	RIGHTPAREN,
	AND,
	OR,
	INEQ,
	RESULTLEVEL,
	NON
};

class Token
{
public:
	TokenType type;
	std::string value;
	Token() : type(NON), value("") {};
	Token(TokenType type, std::string value) : type(type), value(value) {};
};


class Lexer
{
public:
	std::vector<Token> tokens;

	Lexer();
	std::vector<Token> tokenize(std::string expression);
};
 
class ASTNode // Abstract Syntax Tree Node
{
public:
	ASTNode* left = nullptr;
	ASTNode* right = nullptr;
	Token token;

	ASTNode() {};
	ASTNode(Token token) : token(token) {};
	ASTNode(Token token, ASTNode* left, ASTNode* right) : token(token), left(left), right(right) {};

	void add(ASTNode* node);
	void shiftTokenDown(Token token);
	bool setOperator(Token token);
	bool isFull();

	bool interpret(float value = 0.0f);
};