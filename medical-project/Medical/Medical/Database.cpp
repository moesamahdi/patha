#pragma once
#include <unordered_map>
#include <vector>
#include "Database.h"
#include "BloodResult.h"
#include "Level.h"
#include "Outcome.h"

std::unordered_map<std::string, BloodResult> DB::BloodResults;
std::unordered_map<std::string, std::vector<Level>> DB::DefaultGuidelines;
std::unordered_map<std::string, Outcome> DB::Outcomes;
std::vector<std::string> DB::HighestRankedOutcomes;