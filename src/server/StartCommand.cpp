//
// Created by or on 22/12/17.
//

#include <unistd.h>
#include <cstdlib>
#include "StartCommand.h"

StartCommand ::StartCommand(vector<GameInfo>* games,pthread_mutex_t &mutex) : Command() {
    gamesList = games;
    this->mutex = mutex;
}

void StartCommand::execute(vector<string> args) {
    //args[0] - client socket, args[1] - room name
    string str = args[0];
    int client = atoi(str.c_str());
    // '-1' for siging that the name is already taken
    char exists[this->msgLength] = "-1There is already a game with this name!";
    if(!(*gamesList).empty()) {
        vector<GameInfo>::iterator it;

        pthread_mutex_lock(&mutex);

        for (it = (*gamesList).begin(); it != (*gamesList).end(); it++) {
            //Compare the input name to the names in the game list
            //Return -1 if already in the list
            if ((*it).getName() == args[1]) {
                ssize_t n = write(client, &exists, sizeof(exists));
                if (n == -1) {
                    throw "Error on writing to socket";
                }
                //We don't want to continue
                close(client); // close the connection because maybe he won't continue
                pthread_mutex_unlock(&mutex);
                return;
            }
        }
        pthread_mutex_unlock(&mutex);
    }
    //The returned massage

    //Push the game to
    pthread_mutex_lock(&mutex);
    GameInfo gInfo(args[1], client);
    cout << "Game name:" << gInfo.getName();
    cout << "\nGame client:" << gInfo.getFirstClient() << endl;
    (*gamesList).push_back(GameInfo(args[1], client));
    vector<GameInfo>::iterator it;
    for (it = (*gamesList).begin(); it != (*gamesList).end(); it++) {
        cout << (*it).getName() << endl;
    }

        pthread_mutex_unlock(&mutex);


    // '1' for siging thats ok
    char msg[this->msgLength] = "1Waiting for the other player...\n";

    //Write result to client
    ssize_t n = write(client,msg, sizeof(msg));
    if (n == -1) {
        throw "Error on writing to socket";
    }
}