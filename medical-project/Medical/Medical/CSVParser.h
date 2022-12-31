#pragma once
#include <string>
#include "Range.h"
#include "Combination.h"

class CSVParser
{
public:
	std::string readFile(std::string filePath);
	void parseBloodResultsCSV(std::string text);
	void parseCombinationsCSV(std::string text);

private:
	Range parseRangeExp(std::string rangeExpression);
	Combination parseCombinationExp(std::string combinationExpression);
};

