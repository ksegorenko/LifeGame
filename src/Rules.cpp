#include "../libs/Rules.h"

#include <map>

std::map<int, char> ConvertStrToMap(std::string Parameter) {
  std::map<int, char> Result;
  for (int i = 0; i < Parameter.size(); i++)
    Result.insert(std::pair<int, int>(Parameter[i] - '0', Parameter[i]));
  return Result;
}

void Rules::SetBirthRules(std::string BirthStr) {
  this->Birth = ConvertStrToMap(BirthStr);
}

void Rules::SetSurviveRules(std::string SurviveStr) {
  this->Survive = ConvertStrToMap(SurviveStr);
}

const std::map<int, char>& Rules::GetBirthRules() const { return this->Birth; }

const std::map<int, char>& Rules::GetSurviveRules() const {
  return this->Survive;
}

std::string Rules::RulesOutput() {
  std::string OutputResult = "B";
  for (auto i = this->Birth.begin(); i != this->Birth.end(); ++i)
    OutputResult += i->second;
  OutputResult += "/S";
  for (auto i = this->Survive.begin(); i != this->Survive.end(); ++i)
    OutputResult += i->second;
  return OutputResult;
}
