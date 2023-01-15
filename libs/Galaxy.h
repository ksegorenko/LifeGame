#pragma once
#include <fstream>
#include <string>
#include <vector>

#include "Rules.h"

class Galaxy {
 public:
  Galaxy() : Size(0), Rule(nullptr) {}
  std::vector<bool>& GetField();
  int GetSize();
  std::string GetName();
  Rules& GetRules();
  friend void operator>>(std::ifstream& fin, Galaxy& Galaxy);

 private:
  std::vector<bool> Field;
  std::string Name;
  int Size;
  Rules* Rule;
};

void SetGalaxyParameters(std::ifstream&, std::string);
