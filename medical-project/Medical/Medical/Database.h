#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include "BloodResult.h"
#include "Level.h"
#include "Outcome.h"

struct DB // Database
{
	static std::unordered_map<std::string, BloodResult> BloodResults; // mapping of result ID to result
	static std::unordered_map<std::string, std::vector<Level>> DefaultGuidelines; // mapping of result ID to levels
	static std::unordered_map<std::string, Outcome> Outcomes; // mapping of outcome ID to outcomes
	static std::vector<std::string> HighestRankedOutcomes; // vector of highest ranking outcome IDs (where 1st element is highest rank) based on the previous 4 maps
};