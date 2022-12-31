#include <string>
#include <vector>
#include "DBController.h"
#include "Database.h"
#include "Level.h"

void DBController::setBloodResultValue(std::string resultID, float value)
{
	BloodResult* bloodResult = &DB::BloodResults[resultID];
	bloodResult->value = value;
	
	std::vector<Level> levels = DB::DefaultGuidelines[resultID];
	// loop through levels and find the correct LevelID based on the input value (e.g. VL, L, N, H etc.)
	std::string correctLevelID;
	size_t levelsSize = levels.size();
	for (size_t i = 0; i < levelsSize; i++)
	{
		Level level = levels[i];
		bool satisfiesRange = level.getRange().ineqAST->interpret(value);
		if (satisfiesRange)
		{
			correctLevelID = level.getLevelID();
			break;
		}
	}
	// set the levelID on the blood result
	bloodResult->levelID = correctLevelID;
}

void DBController::rankOutcomes()
{
	// loop through outcomes and interpret the result level combination trees
	for (auto& outcomePair : DB::Outcomes)
	{
		Outcome& outcome = outcomePair.second;
		ASTNode* resultLevelTree = outcome.resultLevelCombination.combAST;
		bool expressionSatisfied = resultLevelTree->interpret();
		if (expressionSatisfied)
		{
			DB::HighestRankedOutcomes.push_back(outcomePair.first);
		}
	}
}
