


#include "Server.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
#define MAX_CONNECTED_CLIENTS 20
#define MAX_COMMAND_LEN 20
#define THREADS_NUM 5
static void *acceptClients(void *);



Server::Server(int port,ClientHandler *clientHandler): port(port), serverSocket(0),clientHandler(clientHandler) ,
                                                       threadPool(ThreadPool(THREADS_NUM)){
    cout << "Server" << endl;
}
void Server::start() {
    // Create a socket point
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        throw "Error opening socket";
    }
    // Assign a local address to the socket
    struct sockaddr_in serverAddress;
    bzero((void *)&serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);
    if (bind(serverSocket, (struct sockaddr *)&serverAddress,
             sizeof(serverAddress)) == -1) {
        throw "Error on binding";
    }
    // Start listening to incoming connection requests
    listen(serverSocket, MAX_CONNECTED_CLIENTS);
    info info_;
    info_.serverSocket = serverSocket;
    info_.handler = clientHandler;
    info_.s = this;

    int rc = pthread_create(&serverThreadId, NULL, &acceptClients, &info_);
    if (rc) {
        cout << "Error: unable to create thread, " << rc << endl;
        return;
    }
    string exitCommand;
    do {
        cin >> exitCommand;
    }
    while (exitCommand != "exit");
    clientHandler->handleExit();
    stop();



}
 void *acceptClients(void *args) {

    struct info *information = (struct info *) args;
//    Server *serverP = information->s;
    // Define the client socket's structures
    struct sockaddr_in clientAddress;
    socklen_t clientAddressLen = sizeof(clientAddress);
    while (true) {
        cout << "Waiting for client connections..." << endl;
        // Accept a new client connection
        int clientSocket = accept(information->serverSocket, (struct sockaddr *)&clientAddress, &clientAddressLen);
        cout << "Client connected" << endl;
        if (clientSocket == -1)
            throw "Error on accept";

//        information->handler->clientThreads(clientSocket);
        DataOfClient *dataOfClient = new DataOfClient();
        dataOfClient->clientHandler = information->handler;
        dataOfClient->clientSocket = clientSocket;
        Task* t = new Task(information->s->runAnalyzeCommand, (void *)dataOfClient);
        information->s->addTask(t);
        //task will be deleted in the threadPool
        //Struct will be deleted in runAnalyzeCommand


    }
}
void Server::addTask(Task *task) {
    this->threadPool.addTask(task);
}


void* Server:: runAnalyzeCommand(void *data) {
    DataOfClient* dataOfClient = (DataOfClient*)data;
    dataOfClient->clientHandler->analyzeCommand(dataOfClient->clientSocket);
    delete(dataOfClient);
}


void Server::stop() {
    pthread_cancel(serverThreadId);
    this->threadPool.terminate();
    close(serverSocket);
    cout << "Server stopped" << endl;
}

void Server::close_() {
    bool isExit = false;
    string str;
    while (!isExit) {
        cin >> str;
        if (str == "exit") {
            isExit = true;
            clientHandler->handleExit();
            stop();
        }
    }
}
//}