#pragma once
#include "AbstractSyntaxTree.h"

class Range
{
public:
	ASTNode* ineqAST = nullptr;
	Range() {};
	Range(ASTNode* ast) : ineqAST(ast) {};
};
