#include "Galaxy.h"
#include "Rules.h"
#include <vector>
#include <iostream>
#include <regex>

std::vector<bool>& Galaxy::GetField() {
	return this->Field;
}

int Galaxy::GetSize() {
	return this->Size;
}

std::string Galaxy::GetName() {
	return this->Name;
}

Rules& Galaxy::GetRules() {
	return *(this->Rules);
}

std::string GetGalaxyName(std::string& str, std::ifstream& fin) {
	std::string Name;
	std::cmatch Result;
	std::regex Regular("(#N)( )([\\w]+)");
	if (std::regex_match(str.c_str(), Result, Regular)) {
		Name = Result[3];
		std::getline(fin, str);
	}
	else {
		std::cout << "WARNING. There is no galaxy's name." << std::endl;
		Name = "Noname";
	}
	return Name;
}

int StrToInt(std::string str) {
	int Result = 0;
	int temp = 1;
	for (int i = str.length() - 1; i >= 0; --i) {
		Result = temp * (str[i] - '0') + Result;
		temp *= 10;
	}
	return Result;
}

int GetGalaxySize(std::string& str, std::ifstream& fin) {
	int Size = 0;
	std::cmatch Result;
	std::regex Regular("(#S)( )([0-9]+)");
	if (std::regex_match(str.c_str(), Result, Regular))
		Size = StrToInt(Result[3]);
	else {
		std::cout << "WARNING. No input galaxy size. Game will start with default galaxy size = 10." << std::endl;
		Size = 10;
	}
	return Size;
}

Rules* GetGalaxyRules(std::string& str, std::ifstream& fin) {
	Rules* rules = new Rules;
	std::cmatch Result;
	std::regex Regular("(#R)( )(B)([0-8]+)(/)(S)([0-8]+)");
	if (std::regex_match(str.c_str(), Result, Regular)) {
		rules->SetBirthRules(Result[4]);
		rules->SetSurviveRules(Result[7]);
		std::getline(fin, str);
	}
	else {
		std::cout << "WARNING. No input galaxy rules. The game will start with B2/S23\n" << std::endl;
		rules->SetBirthRules("3");
		rules->SetSurviveRules("23");
	}
	return rules;
}

std::vector<bool> GetFieldVector(std::string& str, std::ifstream& fin, int Size) {
	std::vector<bool> Field(Size * Size, false);
	std::cmatch Result;
	std::regex Regular("([0-9]+)( )([0-9]+)");
	bool IsFieldEmpty = true;
	while (std::getline(fin, str)) {
		if (std::regex_match(str.c_str(), Result, Regular)) {
			if(StrToInt(Result[1]) < Size && StrToInt(Result[3]) < Size)
				Field[StrToInt(Result[1]) * Size + StrToInt(Result[3])] = true;
				IsFieldEmpty = false;
		}
		else
			std::cout << "WARNING. Cell (" << Result[1] << "," << Result[3] << ") is out of galaxy range.\n";
		if (IsFieldEmpty) {
			std::cout << "WARNING. Field is empty.\n";
		}
		return Field;
	}
}

void operator >> (std::ifstream& fin, Galaxy& Galaxy) {
	std::string str;
	std::getline(fin, str);
	if (str != "#Life 1.06") {
		std::cout << "[ERROR] Input file has to be in #Life 1.06 format.";
	}
	std::getline(fin, str);
	Galaxy.Name = GetGalaxyName(str, fin);
	Galaxy.Rules = GetGalaxyRules(str, fin);
	Galaxy.Size = GetGalaxySize(str, fin);
	Galaxy.Field = GetFieldVector(str, fin, Galaxy.Size);
}
