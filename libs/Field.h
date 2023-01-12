#pragma once
#include "Galaxy.h"
#include <vector>

class Field {
public:
	Field() : Size(0) {};
	Field(Galaxy&);
	bool GetCell(int x, int y) const;
	int GetSize();
	void CreateNext(Galaxy& Galaxy);
private:
	int Size;
	std::vector<bool> CurrentField;
	std::vector<bool> NextField;
};
