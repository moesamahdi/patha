#pragma once
#include "Outcome.h"
#include "Combination.h"

Outcome::Outcome()
{
	this->outcomeText = "";
	this->suggestionText = "";
	Combination combination;
	this->resultLevelCombination = combination;
}