#include <iostream>
#include <string>
#include <sstream>
#include "Game.h"
#include "Commands.h"

namespace {
    std::vector<std::string> SplitIntoDifArgs(const std::string& Str, char separator) {
        std::vector<std::string> args;
        std::stringstream stream;
        stream.str(Str);
        std::string item;
        while (std::getline(stream, item, separator)) {
            args.push_back(item);
        }
        return args;
    }

    std::map<std::string, std::unique_ptr<ICommand>> CreateCommandList() {
        std::map<std::string, std::unique_ptr<ICommand>> commandList;

        auto creator = std::unique_ptr<ICommandCreator>{ new ExitCreator };
        commandList.insert(std::pair<std::string, std::unique_ptr<ICommand>>("exit", creator->create()));

        creator = std::unique_ptr<ICommandCreator>{ new HelpCreator };
        commandList.insert(std::pair<std::string, std::unique_ptr<ICommand>>("help", creator->create()));

        creator = std::unique_ptr<ICommandCreator>{ new TickCreator };
        commandList.insert(std::pair<std::string, std::unique_ptr<ICommand>>("tick", creator->create()));

        creator = std::unique_ptr<ICommandCreator>{ new PlayCreator };
        commandList.insert(std::pair<std::string, std::unique_ptr<ICommand>>("play", creator->create()));

        creator = std::unique_ptr<ICommandCreator>{ new DumpCreator };
        commandList.insert(std::pair<std::string, std::unique_ptr<ICommand>>("dump", creator->create()));

        return commandList;
    }
}

void Game::StartGame(Field& field, Galaxy& galaxy) {
    auto commandList = CreateCommandList();

    while (true) {
        std::string line;
        std::getline(std::cin, line);
        std::vector<std::string> args = SplitIntoDifArgs(line, ' ');

        auto it = commandList.find(args[0]);
        if (it != commandList.end()) {
            ICommand* command = it->second.get();
            try {
                int res = command->execute(field, galaxy, args);
                if (res == 0) break;
            }
            catch (CommandExceptions& ex) {
                std::cout << ex.what() << std::endl;
            }
        }
        else {
            std::cout << "I don't know this command.\nType \"help\" to get commands list.\n";
        }
    }
}