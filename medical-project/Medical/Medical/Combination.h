#pragma once
#include "AbstractSyntaxTree.h"

class Combination
{
public:
	ASTNode* combAST = nullptr;
	Combination() {};
	Combination(ASTNode* ast) : combAST(ast) {};
};

