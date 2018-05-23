//
// Created by or on 06/12/17.
//

#ifndef REVERSI_CLIENT_H
#define REVERSI_CLIENT_H

#include "Printer.h"

#define SIZEIP 16

class Client {
public:
    Client(const char *serverIP, int serverPort);
    Client(const char* fileName);
    void connectToServer();
    void closeClient();
    int getClientSocket() const;
    int getPriorityValue();
    int getCommand(Printer* p, bool first);
    const char * getServerIp(){
        return serverIP;
    }

private:
    char serverIP[SIZEIP];
    int serverPort;
    int clientSocket;
};


#endif //REVERSI_CLIENT_H