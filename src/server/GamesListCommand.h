//
// Created by or on 27/12/17.
//

#ifndef REVERSI_LISTGAMESCOMMAND_H
#define REVERSI_LISTGAMESCOMMAND_H


#include "Command.h"

class GamesListCommand : public Command {
public:
    /**
     * constructor.
     * @param gamesList - vector of the game.
     */
    GamesListCommand(vector<GameInfo> *gamesList,pthread_mutex_t &mutex);
    /**
     *
     * @param args
     */
    virtual void execute(vector<string> args);
    /**
     * destrucror
     */
    //~GamesListCommand() {};
private:
//    pthread_mutex_t mutex;
    vector<GameInfo> *gamesList;


};


#endif //REVERSI_LISTGAMESCOMMAND_H
