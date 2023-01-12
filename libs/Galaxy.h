#pragma once
#include <fstream>
#include <vector>
#include <string>
#include "Rules.h"

class Galaxy {
public:
	Galaxy() : Size(0), Rules(nullptr) {}
	std::vector<bool>& GetField();
	int GetSize();
	std::string GetName();
	Rules& GetRules();
	friend void operator >> (std::ifstream& fin, Galaxy& Galaxy);
private:
	std::vector<bool> Field;
	std::string Name;
	int Size;
	Rules* Rules;
};

void SetGalaxyParameters(std::ifstream&, std::string);
