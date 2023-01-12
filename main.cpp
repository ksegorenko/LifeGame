#include <iostream>
#include "Parser.h"
#include "Galaxy.h"
#include "Rules.h"
#include "Field.h"
#include "Commands.h"
#include "Game.h"

int main(int argc, char* argv[]) {
	try {
		Parser Parser;
		Parser.CheckCommandLineArguments(argc, argv);

		Galaxy Galaxy;
		Parser.GetFin() >> Galaxy;

		Field Field(Galaxy);

		Game game;
		game.StartGame(Field, Galaxy);

		return 0;
	}
	catch (std::exception& ex){
		std::cout << ex.what() << std::endl;
		return 1;
	}
}
