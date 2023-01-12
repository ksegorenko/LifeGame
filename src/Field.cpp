#include <iostream>
#include <vector>
#include "Field.h"

int Field::GetSize() {
	return this->Size;
}

Field::Field(Galaxy& Galaxy) {
	CurrentField = Galaxy.GetField();
	NextField = CurrentField;
	this->Size = Galaxy.GetSize();
}

bool Field::GetCell(int x, int y) const {
	return CurrentField[x * Size + y];
}

bool IsAlive(bool Cell) {
	if (Cell == true)
		return true;
	else
		return false;
}

bool IsSurvive(int Neighbors, const std::map<int, char>& SurviveRules) {
	for (auto it = SurviveRules.begin(); it != SurviveRules.end(); ++it) {
		if (Neighbors < it->first) return false;
		if (Neighbors == it->first) return true;
	}
	return false;
}

bool IsBorn(int Neighbors, const std::map<int, char>& BornRules) {
	for (auto it = BornRules.begin(); it != BornRules.end(); ++it) {
		if (Neighbors < it->first)
			return false;
		if (Neighbors == it->first)
			return true;
	}
	return false;
}

int GetUpper(const std::vector<bool>& Field, int CurrentPosition, int Height, int Width) {
	if (CurrentPosition < Width)
		return Field[Height * Width - Width + CurrentPosition] ? 1 : 0;
	else
		return Field[CurrentPosition - Width] ? 1 : 0;
}

int GetUpperRight(const std::vector<bool>& Field, int CurrentPosition, int Height, int Width) {
	if ((CurrentPosition < Width) || ((CurrentPosition + 1) % Width == 0)) 
		return 0;
	else
		return Field[CurrentPosition - Width + 1] ? 1 : 0;
}

int GetRight(const std::vector<bool>& Field, int CurrentPosition, int Height, int Width) {
	if ((CurrentPosition + 1) % Width == 0) {
		return Field[CurrentPosition - Width + 1] ? 1 : 0;
	}
	else {
		return Field[CurrentPosition + 1] ? 1 : 0;
	}
}

int GetBottomRight(const std::vector<bool>& Field, int CurrentPosition, int Height, int Width) {
	if (((CurrentPosition + 1) % Width == 0) || (CurrentPosition >= (Height * Width - Width))) {
		return 0;
	}
	else {
		return Field[CurrentPosition + Width + 1] ? 1 : 0;
	}
}

int GetBottom(const std::vector<bool>& Field, int CurrentPosition, int Height, int Width) {
	if (CurrentPosition >= (Height * Width - Width)) {
		return Field[(CurrentPosition + Width) % (Width * Height)] ? 1 : 0;
	}
	else {
		return Field[CurrentPosition + Width] ? 1 : 0;
	}
}

int GetBottomLeft(const std::vector<bool>& Field, int CurrentPosition, int Height, int Width) {
	if ((CurrentPosition % Width == 0) || (CurrentPosition >= (Height * Width - Width))) {
		return 0;
	}
	else {
		return Field[CurrentPosition + Width - 1] ? 1 : 0;
	}
}

int GetLeft(const std::vector<bool>& Field, int CurrentPosition, int Height, int Width) {
	if (CurrentPosition % Width == 0) {
		return Field[CurrentPosition + Width - 1] ? 1 : 0;
	}
	else {
		return Field[CurrentPosition - 1] ? 1 : 0;
	}
}

int GetUpperLeft(const std::vector<bool>& Field, int CurrentPosition, int Height, int Width) {
	if ((CurrentPosition % Width == 0) || (CurrentPosition < Width)) {
		return 0;
	}
	else {
		return Field[CurrentPosition - Width - 1] ? 1 : 0;
	}
}

int GetNeighbors(const std::vector<bool>& Field, int CurrentPosition, int Height, int Width) {
	return GetUpper(Field, CurrentPosition, Height, Width) +
		+GetUpperRight(Field, CurrentPosition, Height, Width) +
		+GetRight(Field, CurrentPosition, Height, Width) +
		+GetBottomRight(Field, CurrentPosition, Height, Width) +
		+GetBottom(Field, CurrentPosition, Height, Width) +
		+GetBottomLeft(Field, CurrentPosition, Height, Width) +
		+GetLeft(Field, CurrentPosition, Height, Width) +
		+GetUpperLeft(Field, CurrentPosition, Height, Width);
}

void Field::CreateNext(Galaxy& Galaxy) {
	int Neighbors = 0;
	for (int i = 0; i < Size; ++i) {
		for (int j = 0; j < Size; ++j) {
			int CurrentPosition = i * Size + j;
			Neighbors = GetNeighbors(CurrentField, CurrentPosition, Size, Size);
			bool IsStayAlive = IsSurvive(Neighbors, Galaxy.GetRules().GetSurviveRules()) && IsAlive(CurrentField[CurrentPosition]);
			bool IsBecameAlive = !IsAlive(CurrentField[CurrentPosition]) && IsBorn(Neighbors, Galaxy.GetRules().GetBirthRules());
			NextField[CurrentPosition] = (IsStayAlive || IsBecameAlive);
		}
	}
	std::swap(CurrentField, NextField);
}

