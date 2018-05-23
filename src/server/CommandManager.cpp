//
// Created by or on 22/12/17.
//

#include "CommandManager.h"
#include "StartCommand.h"
#include "GamesListCommand.h"
#include "JoinCommand.h"

CommandManager::CommandManager(vector<GameInfo> *gameList, pthread_mutex_t &mutex) {
    // here we crate all the options of command
    // ctrate StartCommand,CloseCommand,Join,listGame

    commandsMap["start"] = new StartCommand(gameList,mutex);
    commandsMap["join"] = new JoinCommand(gameList,mutex);
    commandsMap["list_games"] = new GamesListCommand(gameList,mutex);
}



void CommandManager::executeCommand(string command, vector<string> args) {
    Command *commandObj = commandsMap[command];
    commandObj->execute(args);
}

CommandManager::~CommandManager() {
    map<string, Command *>::iterator it;
    for (it = commandsMap.begin(); it != commandsMap.end(); it++) {
        delete it->second;
    }
}
