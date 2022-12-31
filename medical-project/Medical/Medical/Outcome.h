#pragma once
#include <string>
#include "Combination.h"

class Outcome
{
public:
	Combination resultLevelCombination;

	Outcome();
	Outcome(Combination combination, std::string outcomeText, std::string suggestionText) : resultLevelCombination(combination), outcomeText(outcomeText), suggestionText(suggestionText) {};

	std::string getOutcomeText() { return outcomeText; }
	std::string getSuggestionText() { return suggestionText; }
private:
	std::string outcomeText;
	std::string suggestionText;
};

