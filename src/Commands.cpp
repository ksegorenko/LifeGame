#include "../libs/Commands.h"

#include <chrono>
#include <iostream>
#include <regex>
#include <sstream>
#include <thread>

namespace {
int convertStrToInt(std::string line) {
  return atoi(line.c_str());
}
}  // namespace

int Exit::execute(Field& field, Galaxy& galaxy, std::vector<std::string> args) {
  return 0;
}

int Help::execute(Field& field, Galaxy& galaxy, std::vector<std::string> args) {
  std::cout << std::endl;
  std::cout << "dump <filename> -- to consrerv the universe in a file\n\n";
  std::cout << "tick <n> -- to calculate n iterations and output result\n\n";
  std::cout << "exit -- to finish the game\n\n";

  return 1;
}

void Tick::outputField(Field& field) {
  for (int i = 0; i < field.GetSize(); ++i) {
    for (int j = 0; j < field.GetSize(); ++j) {
      std::cout << (field.GetCell(i, j) == true ? "# " : ". ");
    }
    std::cout << std::endl;
  }
}

int Tick::execute(Field& field, Galaxy& galaxy, std::vector<std::string> args) {
  if (args.size() > 1) {
    int numIterat = convertStrToInt(args[1]);
    while (numIterat > 0) {
      field.CreateNext(galaxy);
      numIterat--;
    }
    outputField(field);
  } else {
    std::cout << "Wrong number of arguments" << std::endl;
  }
  return 2;
}

void Play::outputField(Field& field) {
  for (int i = 0; i < field.GetSize(); ++i) {
    for (int j = 0; j < field.GetSize(); ++j) {
      std::cout << (field.GetCell(i, j) == true ? "# " : ". ");
    }
    std::cout << std::endl;
  }
}

int Play::execute(Field& field, Galaxy& galaxy, std::vector<std::string> args) {
  if (args.size() > 1) {
    int numIterat = convertStrToInt(args[1]);
    while (numIterat > 0) {
      system("cls");
      field.CreateNext(galaxy);
      outputField(field);
      std::this_thread::sleep_for(std::chrono::milliseconds(500));
      numIterat--;
    }
  } else {
    std::cout << "Wrong number of arguments" << std::endl;
  }

  return 3;
}

void Dump::outputField(std::ofstream& output, Field& field) {
  for (int i = 0; i < field.GetSize(); ++i) {
    for (int j = 0; j < field.GetSize(); ++j) {
      if (field.GetCell(i, j) == true) {
        output << i << " " << j << std::endl;
      }
    }
  }
}

int Dump::execute(Field& field, Galaxy& galaxy, std::vector<std::string> args) {
  std::ofstream output;
  std::cmatch result;
  std::regex reg("[\\w]+.txt$");
  if (args.size() > 1) {
    if (std::regex_match(args[1].c_str(), result, reg)) {
      output.open(args[1]);
      if (output.is_open()) {
        output << "#Life 1.06\n";
        output << "#N " << galaxy.GetName() << std::endl;
        output << "#R " << galaxy.GetRules().RulesOutput() << std::endl;
        output << "#S " << galaxy.GetSize() << std::endl;
        outputField(output, field);
      } else
        throw std::invalid_argument("I can't open this file. Try again.");

    } else {
      throw std::invalid_argument(
          "File has to be with \"txt\" format. Try again.");
    }
  } else {
    std::cout << "Wrong number of arguments" << std::endl;
  }
  output.close();

  return 4;
}
