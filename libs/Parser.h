#pragma once
#include <fstream>
#include <iostream>

class Parser {
public:
	void CheckCommandLineArguments(int argc, char* argv[]);
	std::ifstream& GetFin();
private:
	std::ifstream fin;
};

class ParsingExceptions : public std::exception {
public:
	ParsingExceptions(const char*) : std::exception() {}
};
