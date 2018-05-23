//
// Created by or on 22/12/17.
//

#ifndef REVERSI_COMMANDMANAGER_H
#define REVERSI_COMMANDMANAGER_H


#include <map>
#include "Command.h"

class CommandManager {
public:
    CommandManager(vector<GameInfo>*gamesList, pthread_mutex_t &mutex);
    ~CommandManager();
    void executeCommand(string command,
                        vector<string> args);
private:
//    pthread_mutex_t mutex;
    map<string, Command *> commandsMap;
};


#endif //REVERSI_COMMANDMANAGER_H
