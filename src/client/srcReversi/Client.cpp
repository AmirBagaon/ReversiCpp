//
// Created by or on 06/12/17.
//

#include "../include/Client.h"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fstream>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include <sstream>
#define REQ 200



using namespace std;


Client::Client(const char* fileName) {
    ifstream file;
    file.open(fileName, ios::in);
    if (!file.is_open())
        throw "Error opening the settings file!";
    else {
        string ip,buffer;
        file >> ip;
        strcpy(this->serverIP , ip.c_str());
        file >> this->serverPort;
        this->clientSocket = 0;

    }
    file.close();
}
void Client::connectToServer() {
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        throw "Error opening socket";
    }
    // Convert the ip string to a network address
    struct hostent *server;
    struct in_addr address;
    if (!inet_aton(serverIP, &address)) {
        throw "Can't parse IP address";
    }
    server = gethostbyaddr((const void *) &address, sizeof address, AF_INET);
    if (server == NULL) {
        throw "Host is unreachable";
    }

    struct sockaddr_in serverAddress;
    bzero((char *)&address, sizeof(address));
    serverAddress.sin_family = AF_INET;
    memcpy((char *)&serverAddress.sin_addr.s_addr,(char *)server->h_addr, server->h_length);
    serverAddress.sin_port = htons(serverPort);
    // Establish a connection with the TCP server
    if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        throw "Error connecting to server";
    }

//    cout << "Connected to server" << endl << "Waiting for the other players..." << endl;
}

int Client::getCommand(Printer* printer, bool first) {
    string toSend;
    char serverAnswer[REQ];
    char buffer[REQ];
    int ignore = first; //to ignore the '\n' from the first choice

    bool isValid = false;
    do {
    printer->massage("\nPlease enter one of the following commands: start <name>, "
                             " join <name>, list_games\n");
    toSend = printer->scanString(ignore);
        istringstream iss(toSend);
        string subs;
        iss >> subs;
        if ((toSend == "list_games") || (subs == "start") ||(subs == "join") ) {
            isValid = true;
        } else {
            printer->massage("\nPlease insert correct command!\n");
            ignore = false;
        }
    } while (!isValid);
    strcpy(buffer, toSend.c_str());

    //Connect to server
    connectToServer();
    if (first){
        printer->massage("Connected to server\n");
    }

    //Send Command to server
    ssize_t n = write(clientSocket,buffer ,sizeof(buffer));
    if (n == -1) {
        throw "Error writing move to socket";
    }

    //Get Server response
    n = read(clientSocket,serverAnswer ,sizeof(serverAnswer));
    if (n == -1) {
        throw "Error reading move from socket";
    }
    if (n == 0) {
        printer->massage("The Server was closed1\n");
        closeClient();
        return -2;
        
//        exit(-1);
    }


    //get the string msg;
    stringstream stream(serverAnswer);
    int num;
    string msg;
    //Split the info-num from server and the message
    while(stream >> num) {
        getline(stream, msg);
    }
    msg.append("\n");

    //For 'join' command, print "connect successfuly"
    //For 'start' command, print "waiting for other player..."
    //For 'list_games' command, print the list
    printer->massage(msg);

    //For 'join' command, need to get the priority
    //For 'start' command, need to get the priority

    //If the request wasn't good or it was list, the loop will repeat
    if(num == -1) {
        closeClient();
        return num;
    }

    int priority = getPriorityValue();
    if (priority <= 0) {
        printer->massage("The Server was closed2\n");
        closeClient();
        return -2;
        
    }
    return priority;

}

int Client::getClientSocket() const{
    return clientSocket;
}

int Client::getPriorityValue() {
    //if priority is 0, it means that it close the game
    int priority;
    ssize_t n = read(clientSocket, &priority, sizeof(priority));
    if (n <= 0) {
        return (int)n;
    }
    return priority;
}
void Client::closeClient(){
    close(clientSocket);
}