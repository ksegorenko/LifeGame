#pragma once
#include <string>
#include <map>

class Rules {
public:
	void SetBirthRules(std::string);
	void SetSurviveRules(std::string);
	const std::map <int, char>& GetBirthRules() const;
	const std::map <int, char>& GetSurviveRules() const;
	std::string RulesOutput();
private:
	std::map<int, char> Birth;
	std::map<int, char> Survive;
};