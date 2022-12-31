#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include "CSVParser.h"
#include "Database.h"
#include "Level.h"
#include "Range.h"
#include "Outcome.h"
#include "BloodResult.h"
#include "AbstractSyntaxTree.h"
#include "ExpressionParser.h"

std::string CSVParser::readFile(std::string filePath)
{
	std::ifstream file(filePath);
	std::stringstream buffer;
	buffer << file.rdbuf();
	std::string text = buffer.str();
	return text;
}

void CSVParser::parseBloodResultsCSV(std::string text)
{
	std::string cellText = ""; // value in the column/cell between commas
	int columnIndex = 0;
	int rowIndex = 0;
	std::unordered_map<std::string, int> columnHeadersMap; // columns should be: BloodResult, ResultID, LevelID1, Range1 ... (repeat LevelID, Range)
	std::vector<std::string> rowValues;
	
	for (char& c : text)
	{
		if (c != ',' && c != '\n') // if character isn't a separator
		{
			if (rowIndex == 0 && c == ' ') // skip spaces in cell text for the first row (column headers), ensures key is consistent
				continue;

			cellText += c;
		}
		else if (c == ',')
		{
			if (rowIndex == 0) // if first row
			{
				columnHeadersMap[cellText] = columnIndex;
			}
			else // add values to rowValues to be processed when the vector is full (all row values are set)
			{
				rowValues[columnIndex] = cellText;
			}
			
			columnIndex += 1;
			cellText = "";
		}
		else if (c == '\n') // reached end of row
		{
			if (rowIndex == 0) // if first row
			{
				columnHeadersMap[cellText] = columnIndex; // add last column
				rowValues.resize(columnHeadersMap.size()); // set size of vector now that its known
			}
			else // add key-value to BloodResultsMap and DefaultGuidelines for current row
			{
				rowValues[columnIndex] = cellText; // add last column

				// BloodResultsMap
				std::string resultID = rowValues[columnHeadersMap["ResultID"]];
				std::string name = rowValues[columnHeadersMap["BloodResult"]];
				BloodResult bloodResult(name);
				DB::BloodResults[resultID] = bloodResult;

				// DefaultGuidelines
				std::vector<Level> levels;
				int numOfRanges = (static_cast<int>(columnHeadersMap.size()) - 2) / 2;
				for (int i = 1; i <= numOfRanges; i++)
				{
					std::string rangeExpression = rowValues[columnHeadersMap["Range" + std::to_string(i)]];
					Range range = this->parseRangeExp(rangeExpression);

					std::string levelID = rowValues[columnHeadersMap["LevelID" + std::to_string(i)]];
					
					Level level(levelID, range);
					levels.push_back(level);
				}

				DB::DefaultGuidelines[resultID] = levels;
			}

			columnIndex = 0;
			rowIndex += 1;
			cellText = "";
		}
	}
}

void CSVParser::parseCombinationsCSV(std::string text)
{
	std::string cellText = ""; // value in the column/cell between commas
	int columnIndex = 0;
	int rowIndex = 0;
	std::unordered_map<std::string, int> columnHeadersMap; // columns should be: OutcomeID, ResultCombination, OutcomeText, SuggestionText
	std::vector<std::string> rowValues;

	for (char& c : text)
	{
		if (c != ',' && c != '\n') // if character isn't a separator
		{
			if (rowIndex == 0 && c == ' ') // skip spaces in cell text for the first row (column headers), ensures key is consistent
				continue;

			cellText += c;
		}
		else if (c == ',')
		{
			if (rowIndex == 0) // if first row
			{
				columnHeadersMap[cellText] = columnIndex;
			}
			else // add values to rowValues to be processed when the vector is full (all row values are set)
			{
				rowValues[columnIndex] = cellText;
			}

			columnIndex += 1;
			cellText = "";
		}
		else if (c == '\n') // reached end of row
		{
			if (rowIndex == 0) // if first row
			{
				columnHeadersMap[cellText] = columnIndex; // add last column
				rowValues.resize(columnHeadersMap.size()); // set size of vector now that its known
			}
			else // add key-value to OutcomesMap for current row
			{
				rowValues[columnIndex] = cellText; // add last column

				// Outcomes
				std::string outcomeID = rowValues[columnHeadersMap["OutcomeID"]];
				std::string outcomeText = rowValues[columnHeadersMap["OutcomeText"]];
				std::string suggestionText = rowValues[columnHeadersMap["SuggestionText"]];
				std::string resultLevelCombinationExp = rowValues[columnHeadersMap["ResultCombination"]];

				Combination resultLevelCombination = this->parseCombinationExp(resultLevelCombinationExp);

				Outcome outcome(resultLevelCombination, outcomeText, suggestionText);

				DB::Outcomes[outcomeID] = outcome;
			}

			columnIndex = 0;
			rowIndex += 1;
			cellText = "";
		}
	}
}

Range CSVParser::parseRangeExp(std::string rangeExpression)
{
	ExpressionParser expParser;
	// create abstract syntax tree representation of the expression
	ASTNode* ineqAST = expParser.parseExpression(rangeExpression);

	Range range(ineqAST);
	//expParser.displayAST(range.ineqAST);
	return range;
}

Combination CSVParser::parseCombinationExp(std::string combinationExpression)
{
	ExpressionParser expParser;
	// // create abstract syntax tree representation of the expression
	ASTNode* combAST = expParser.parseExpression(combinationExpression);
	
	Combination combination(combAST);
	//expParser.displayAST(combination.combAST);
	return combination;
}