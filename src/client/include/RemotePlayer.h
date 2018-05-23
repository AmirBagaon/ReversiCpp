//
// Created by or on 06/12/17.
//

#ifndef REVERSI_REMOTEPLAYER_H
#define REVERSI_REMOTEPLAYER_H

#include "Player.h"
#include "Client.h"

class RemotePlayer : public Player {
private:
    const Client *client;
    int priority;
    Printer* printer;

public:
    /************************************************************************
	* Name: RemotePlayer (Constructor)
	* Input: t- The player's token, client - the client connection to server.
    * also printer and player's priority
	* Output: -
	* Operation:
	*************************************************************************/
    RemotePlayer(const Value t ,const  Client* client, Printer* printer, int priority);

    /************************************************************************
    * Name: sendCoordinate
    * Input: coordinate
    * Output: -
    * Operation: Send coordinate to server
    *************************************************************************/
    void sendCoordinate(Coordinate &coordinate) const;
    /************************************************************************
    * Name: getCoordinateFromServer
    * Input: coordinate
    * Output: -
    * Operation: get coordinate from server
    *************************************************************************/
    void getCoordinateFromServer(Coordinate &coordinate) const;

    virtual Coordinate makeTurn(Logic* l, Board* b, set<Coordinate> availableMoves);
    virtual void startTurn(const Value &sign, Coordinate c) const;
    virtual void cantMove(Logic* l) const;
};


#endif //REVERSI_REMOTEPLAYER_H
