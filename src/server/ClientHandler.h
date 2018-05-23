//
// Created by amir on 26/12/17.
//

#ifndef REVERSI_CLIENTHANDLER_H
#define REVERSI_CLIENTHANDLER_H


#include <vector>
#include "GameInfo.h"
#include "CommandManager.h"

class ClientHandler {

    struct DataOfClient{
        ClientHandler *clientHandler;
        int clientSocket;
    };

private:
    vector<GameInfo> *gamesList;
    CommandManager* commandManager;
    vector<pthread_t> *threads;
    pthread_mutex_t threadsMutex;
    pthread_mutex_t mutex;

public:
    ClientHandler();
    ~ClientHandler();
//    void handleClient(int Socket);
    //void closeThreads();
//    void clientThreads(int client);
    void analyzeCommand(int client);
    void handleExit();

};





#endif //REVERSI_CLIENTHANDLER_H
