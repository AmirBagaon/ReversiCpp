

#ifndef REVERSI_PLAYER_H
#define REVERSI_PLAYER_H

#include <iostream>
#include "Printer.h"
#include "Logic.h"

using namespace std;

class Player {

protected:
    const Value sign;

public:
    /************************************************************************
	* Name: Player (Constructor)
	* Input: token - The player's token
	* Output: -
	* Operation: Matches a player with a token
	*************************************************************************/
    Player(const Value t);

    /************************************************************************
	* Name: ~Player (Destructor)
	* Input: -
	* Output: -
	* Operation: Not in use right now
	*************************************************************************/
    virtual ~Player();

    /************************************************************************
    * Name: GetToken
    * Input: -
    * Output: Returns the player token
    * Operation: " " "
    *************************************************************************/
    virtual Value getToken();

    /************************************************************************
    * Name: startTurn
    * Input: -
    * Output:
    * Operation: Start the turn of the player. print valubale massages
    *************************************************************************/
    virtual void startTurn( const Value &sign, Coordinate c) const = 0;
    /************************************************************************
    * Name: cantMove
    * Input: -
    * Output:
    * Operation: Respone to a situation that the player cant move
    *************************************************************************/
    virtual void cantMove( Logic* l) const = 0;

    /************************************************************************
    * Name: MakeTurn
    * Input: -
    * Output: -
    * Operation: Make the turn after the player chooses row and col
    *************************************************************************/
    virtual Coordinate makeTurn(Logic* l, Board* b, set<Coordinate> availableMoves) = 0;
};


#endif //REVERSI_PLAYER_H
