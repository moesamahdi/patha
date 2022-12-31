#include <iostream>
#include "ExpressionParser.h"

ASTNode* ExpressionParser::parseExpression(std::string expression)
{
	std::vector<Token> tokens = this->lexer.tokenize(expression);

	int iterator = 0;
	ASTNode* ASTRootNode = this->createASTNode(tokens, iterator);

	return ASTRootNode;
}

ASTNode* ExpressionParser::createASTNode(std::vector<Token> tokens, int& iterator)
{
	ASTNode* node = new ASTNode;

	size_t tokensSize = tokens.size();
	for (int& i = iterator; i < tokensSize; i++)
	{
		Token token = tokens[i];
		if (token.type == LEFTPAREN)
		{
			i++;
			ASTNode* childNode = this->createASTNode(tokens, i);
			node->add(childNode);
		}
		else if (token.type == RIGHTPAREN)
		{
			if (node->isFull())
				return node;
			else
			{
				throw std::exception("ERROR: Expression in parentheses not complete.");
			}
		}
		else if (token.type == INEQ || token.type == RESULTLEVEL)
		{
			if (node->token.type == NON)
			{
				node->token = token;
			}
			else
			{
				ASTNode* leafNode = new ASTNode(token);
				node->add(leafNode);
			}
		}
		else if (token.type == AND || token.type == OR)
		{
			bool successfullySet = node->setOperator(token);
			if (successfullySet == false) // if this node's operator is already set to an operator
			{
				// at this point we already have a complete expression (the tree's left and right
				// nodes are occupied) but we've run into another operator, so we need to need go
				// back one char to the operand (that would be on the right node) and create a sub tree,
				// then replace the right node with this sub tree, this will happen for example with (A & B | C)
				i--;
				ASTNode* childNode = this->createASTNode(tokens, i);
				node->right = childNode;
			}
		}
	}

	return node;
}

void ExpressionParser::displayAST(ASTNode* root, int level)
{
	if (root == nullptr)
	{
		return;
	}

	// Print the current node value
	for (int i = 0; i < level; i++) {
		std::cout << "   ";
	}
	std::cout << root->token.value << std::endl;

	// Print the left and right subtrees
	this->displayAST(root->left, level + 1);
	this->displayAST(root->right, level + 1);
}