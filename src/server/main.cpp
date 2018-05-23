#include "Server.h"
#include "ClientHandler.h"
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>

using namespace std;
int main() {
    ClientHandler *clientHandler = new ClientHandler();
    int port;
    ifstream inFile;
    inFile.open("setting_server.txt");
    if(!inFile.is_open()) {
        throw "Can't open file";
    }
    string line;
    while (getline(inFile,line)) {
        if(line[0] == '#') continue;

        stringstream(line) >> port;
    }
    inFile.close();
    Server server(port, clientHandler);
    try {
        server.start();

    } catch (const char *msg) {
        cout << "Cannot start server. Reason: " << msg << endl;
        delete clientHandler;
        exit(-1);
    }
    delete clientHandler;
}
