#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include <stack>
#include <exception>
#include "AbstractSyntaxTree.h"
#include "Inequality.h"
#include "Database.h"

Lexer::Lexer()
{
	// tokens size is assumed to be no bigger than 50 elements
	this->tokens.resize(0);
}

std::vector<Token> Lexer::tokenize(std::string expression)
{
	// TODO: refactor, add error handling: tokens size is assumed to be no bigger than 50 elements
	int numOfTokens = 0;
	std::string operandStr = ""; // string buffer containing operand (Inequality e.g. <40 or Result Level e.g. B1L)
	std::string::size_type expressionLength = expression.size();
	for (std::string::size_type i = 0; i < expressionLength; i++)
	{
		char c = expression[i];
		if (c == ' ')
			continue;
		else if (c == '(' || c == ')' || c == '+' || c == '/')
		{
			if (operandStr != "")
			{
				// if reached a different token to OPERAND then finally add it as token
				Token token;
				if (operandStr[0] == '<' || operandStr[0] == '>')
					token.type = INEQ;
				else
					token.type = RESULTLEVEL;
				token.value = operandStr;
				this->tokens.push_back(token);
				operandStr = "";
				numOfTokens += 1;
			}
			
			TokenType type;
			if (c == '(') type = LEFTPAREN;
			else if (c == ')') type = RIGHTPAREN;
			else if (c == '+') type = AND;
			else if (c == '/') type = OR;
			Token token(type, std::string(1, c));
			this->tokens.push_back(token);
			numOfTokens += 1;
		}
		else
		{
			operandStr += c;
		}

		if (i == expressionLength - 1 && operandStr != "") // if at last element, make sure to add operandStr if anything is in it
		{
			Token token;
			if (operandStr[0] == '<' || operandStr[0] == '>')
				token.type = INEQ;
			else
				token.type = RESULTLEVEL;
			token.value = operandStr;
			this->tokens.push_back(token);
			numOfTokens += 1;
		}
	}

	this->tokens.resize(numOfTokens);
	return this->tokens;
}

void ASTNode::add(ASTNode* node)
{
	if (this->left == nullptr)
	{
		this->left = node;
	}
	else if (this->right == nullptr)
	{
		this->right = node;
	}
	else
	{
		// throw error if both occupied
		throw std::exception("ERROR: Failed to add node, both left and right are occupied.");
	}
}

void ASTNode::shiftTokenDown(Token newToken)
{
	// put token in this node into a leaf node, replace this token with new incoming token
	ASTNode* leafNode = new ASTNode(this->token);
	this->token = newToken;
	this->add(leafNode);
}

bool ASTNode::setOperator(Token token)
{
	if (this->token.type == NON)
	{
		this->token = token;
		return true;
	}
	else if (this->token.type == INEQ || this->token.type == RESULTLEVEL)
	{
		this->shiftTokenDown(token);
		return true;
	}
	else
	{
		return false;
	}
}

bool ASTNode::isFull()
{
	if (this->token.type != NON && this->left != nullptr && this->right != nullptr)
		return true;
	else
		return false;
}


bool ASTNode::interpret(float value)
{
	if (this->token.type == INEQ)
	{
		Inequality ineq(this->token.value);
		bool inequalitySatisfied = ineq.interpret(value);
		return inequalitySatisfied;
	}
	else if (this->token.type == RESULTLEVEL)
	{
		// resultLevel is in the format ResultID.LevelID, find these from the string first
		std::string resultLevel = this->token.value;
		std::string resultID = "";
		std::string levelID = "";
		bool addToResultID = true;
		for (char& c : resultLevel)
		{
			if (c == '.')
			{
				addToResultID = false;
				continue;
			}
			if (addToResultID == true) resultID += c;
			else levelID += c;
		}

		// now find the BloodResult using the ResultID and check if the LevelID matches
		if (DB::BloodResults[resultID].levelID == levelID) return true;
		else return false;
	}
	else if (this->token.type == AND)
	{
		return this->left->interpret(value) && this->right->interpret(value);
	}
	else if (this->token.type == OR)
	{
		return this->left->interpret(value) || this->right->interpret(value);
	}
	else return false; // if node is empty (no expression)
}