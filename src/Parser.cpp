#include "../libs/Parser.h"

#include <fstream>

void Parser::CheckCommandLineArguments(int argc, char* argv[]) {
  if (argc != 2)
    throw std::invalid_argument(
        "ERROR. Please, enter the correct number of arguments to the command "
        "line.");
  this->fin.open(argv[1]);
  if (!this->fin.is_open())
    throw std::invalid_argument(
        "ERROR. Input file can not be opened. Please, try again.");
}

std::ifstream& Parser::GetFin() { return this->fin; }
