#pragma once
#include <string>

class Inequality
{
public:
	std::string symbol; // inequality symbol i.e. <, >, <=, >=
	float num;

	Inequality() : symbol(""), num(0) {};
	Inequality(std::string ineqStr);

	bool interpret(float value);
};