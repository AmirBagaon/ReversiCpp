//
// Created by or on 06/12/17.
//
#include <iostream>
#include <string>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include "../include/RemotePlayer.h"
#include "../include/Client.h"



using namespace std;
RemotePlayer::RemotePlayer(const Value t, const Client *client, Printer* printer1,
                           int p) : Player(t), priority(p), client(client) , printer(printer1){
}

Coordinate RemotePlayer::makeTurn(Logic* logic, Board* originalBoard,
                                  set<Coordinate> availableMoves) {
    Coordinate c = logic->getLastMove();
    if (priority == 1) { //We dont want the second player to send coordinate at first turn
        sendCoordinate(c);
    }
    if (c.getRow() == -8) {
        return c;
    }

    priority = 1;
    getCoordinateFromServer(c);
    return c;
}



void RemotePlayer::sendCoordinate(Coordinate &coordinate) const{
    int move[2];
    move[0] = coordinate.getRow();
    move[1] = coordinate.getCol();

    try {
        ssize_t n = write(client->getClientSocket(),move ,sizeof (move));
        if (n == -1) {
            throw "Error writing move to socket";
        }
        if (n == 0) {
            coordinate = Coordinate(-8, -8);
            return;
        }
    } catch (const char *msg) {
        cout << "Problem detected: " << msg << endl;
        cout << "You should restart the game";
        char a;
        cin >> a;
    }
}

void RemotePlayer::getCoordinateFromServer(Coordinate &coordinate) const{
    int move[2];
    try {
        ssize_t n = read(client->getClientSocket(),move ,sizeof (move));
        if (n == -1) {

            throw "Error reading move from socket";
        }
        if (n == 0) {
//            printer->massage("The Server was closed4\n");
              coordinate = Coordinate(-8, -8);
            return;
//            coordinate = Coordinate(-8, -8); // the server close (indicate for it)
//            return;
        }
        coordinate = Coordinate(move[0], move[1]);
    }catch (const char *msg) {
        printer->massage("Problem detected: ");
        printer->massage(msg);
        printer->massage("You should restart the game");
        exit(-1);
    }
}

void RemotePlayer::startTurn(const Value &sign, Coordinate c) const {
    printer->massage("waiting for other player's move...\n");
}
void RemotePlayer::cantMove(Logic* l) const {

    Coordinate c = l->getLastMove();
    sendCoordinate(c);
    getCoordinateFromServer(c);

    if ((c.getRow() == - 2) && (c.getCol() == -2)) {
        l->couldntMove();
    }
}











