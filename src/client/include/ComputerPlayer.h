

#ifndef REVERSI_ComputerPLAYER_H
#define REVERSI_ComputerPLAYER_H


#include "Player.h"

class ComputerPlayer: public Player {
public:
    /************************************************************************
   * Name: ComputerPlayer (Constructor)
   * Input: t- The player's token
   * Output: -
   * Operation: Matches a player with a token
   *************************************************************************/
    ComputerPlayer(const Value t, Printer* p);
    /************************************************************************
    * Name: ~ComputerPlayer (Destructor)
    * Input: -
    * Output: -
    * Operation: Not in use right now
    *************************************************************************/
    ~ComputerPlayer();

    /************************************************************************
    * Name: MakeTurn
    * Input: -
    * Output: -
    * Operation: Gets a row and a col from the Computer player and makes a move.
     * Calculate the best option for the computer by minMax algorithm.
    *************************************************************************/
    virtual Coordinate makeTurn(Logic* l, Board* originalBoard, set<Coordinate> availableMoves);
    virtual void startTurn( const Value &sign, Coordinate c) const;
    virtual void cantMove( Logic* l) const;

private:
    Printer* printer;
};


#endif //REVERSI_ComputerPLAYER_H
