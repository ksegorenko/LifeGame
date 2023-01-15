#include <iostream>

#include "libs/Commands.h"
#include "libs/Field.h"
#include "libs/Galaxy.h"
#include "libs/Game.h"
#include "libs/Parser.h"
#include "libs/Rules.h"

int main(int argc, char* argv[]) {
  try {
    Parser parser;
    parser.CheckCommandLineArguments(argc, argv);

    Galaxy galaxy;
    parser.GetFin() >> galaxy;

    Field field(galaxy);

    Game game;
    game.StartGame(field, galaxy);
  } catch (std::exception& ex) {
    std::cout << ex.what() << std::endl;
  }
}
