#pragma once
#include <string>
#include <vector>
#include "AbstractSyntaxTree.h"

class ExpressionParser // String Expression to AST parser
{
public:
	Lexer lexer;
	ASTNode* createASTNode(std::vector<Token> tokens, int& iterator);
	ASTNode* parseExpression(std::string expression);

	void displayAST(ASTNode* root, int level = 0);
};

