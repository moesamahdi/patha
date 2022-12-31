#pragma once
#include "Inequality.h"

Inequality::Inequality(std::string inqStr)
{
	std::string numBuffer = "";
	for (char& c : inqStr)
	{
		if (c == '<' || c == '>' || c == '=')
		{
			this->symbol += c;
		}
		else
		{
			numBuffer += c;
		}
	}

	this->num = stoi(numBuffer);
}

bool Inequality::interpret(float value)
{
	if (this->symbol == ">") if (value > this->num) return true; else return false;
	else if (this->symbol == "<") if (value < this->num) return true; else return false;
	else if (this->symbol == ">=") if (value >= this->num) return true; else return false;
	else if (this->symbol == "<=") if (value <= this->num) return true; else return false;
	else return false;
}