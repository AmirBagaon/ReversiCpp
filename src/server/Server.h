////
//// Created by or on 05/12/17.
////
//
#ifndef REVERSI_SERVER_H
#define REVERSI_SERVER_H
//
//
#include "ClientHandler.h"
#include "ThreadPool.h"
#include <pthread.h>
class Server {
public:
    Server(int port,ClientHandler *clientHandler);
    void start();
    void stop();
    void close_();
    void addTask(Task *task);


    static void *runAnalyzeCommand(void *data);

private:
    int port;
    int serverSocket; // the socket's file descriptor
    pthread_t serverThreadId;
    ClientHandler* clientHandler;
    ThreadPool threadPool;


};
struct DataOfClient{
    ClientHandler *clientHandler;
    int clientSocket;
};
typedef struct info {
    int serverSocket;
    ClientHandler *handler;
    Server* s;
}info;


#endif //REVERSI_SERVER_H
