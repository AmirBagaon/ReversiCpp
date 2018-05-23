//
// Created by or on 27/12/17.
//

#include <list>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include "GamesListCommand.h"
GamesListCommand ::GamesListCommand(vector<GameInfo> *games,pthread_mutex_t &mutex) {
    gamesList = games;
    this->mutex = mutex;

}
void GamesListCommand :: execute(vector<string> args) {
    //args contains: args[0]-client, args[1]- nothing
    string str = args[0];
    int client = atoi(str.c_str());

    list<string> gamesNames;
    vector<GameInfo>::iterator it;

    pthread_mutex_lock(&mutex);
    if(gamesList->empty()) {
        char msg[this->msgLength] = "-1There are no available rooms !";
        //Write result to client
        ssize_t n = write(client,msg, sizeof(msg));
        if (n == -1) {
            throw "Error on writing to socket";
        }
//        pthread_mutex_unlock(&mutex);
        return;
    }
    for (it = gamesList->begin(); it != gamesList->end(); ++it) {
        // means that no one already connected to game.
        if(it->getSecondClient() == -1 ) {
            gamesNames.push_back((*it).getName());
            cout << "List: \n";
            cout  << (*it).getName();
        }

    }
    pthread_mutex_unlock(&mutex);

    //Make it as one long string, to send it as string
    string namesInString = "-1"; //-1 to info the client it should send another command
    list<string>::iterator listIT;
    for (listIT = gamesNames.begin(); listIT  != gamesNames.end();) {
        namesInString.append(*(listIT));
        //join "\n" except from the last time
        if (++listIT != gamesNames.end()) {
            namesInString.append(", ");
        } else {
            namesInString.append("\0");
        }
    }
    cout << namesInString << endl;
    const char* toSend = namesInString.c_str();
    cout << toSend << endl;
    char msg[this->msgLength];
    strcpy(msg, toSend);
    cout << msg;


    ssize_t n = write(client,msg, sizeof(msg));
    if (n==-1) {
        throw "Error while writing to socket";
    }

    //At the end, the player get the list, and we close the socket
    close(client);

}