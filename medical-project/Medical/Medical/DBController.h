#pragma once
#include <string>

class DBController
{
public:
	void setBloodResultValue(std::string resultID, float value);
	void rankOutcomes();
};

