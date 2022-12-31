#pragma once
#include <string>

class BloodResult
{
public:
	float value;
	std::string levelID; // e.g. VL (very low), L (low), N (normal), H (high) etc.

	BloodResult(std::string name = "") : name(name), value(0.0f) {};
private:
	std::string name;
};

