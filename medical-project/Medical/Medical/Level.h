#pragma once
#include <string>
#include "Range.h"


class Level
{
public:
	Level(std::string levelID, Range range) : levelID(levelID), range(range) {};
	std::string getLevelID() { return levelID; };
	Range getRange() { return range; };
private:
	std::string levelID; // e.g. L/N/H
	Range range;
};