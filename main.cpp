#include <iostream>
#include "Parser.h"
#include "Galaxy.h"
#include "Rules.h"
#include "Field.h"
#include "Commands.h"
#include "Game.h"

int main(int argc, char* argv[]) {
	try {
		Parser parser;
		parser.CheckCommandLineArguments(argc, argv);

		Galaxy galaxy;
		parser.GetFin() >> galaxy;

		Field field(galaxy);

		Game game;
		game.StartGame(field, galaxy);

		return 0;
	}
	catch (std::exception& ex){
		std::cout << ex.what() << std::endl;
		return 1;
	}
}
