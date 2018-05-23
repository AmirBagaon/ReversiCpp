

#ifndef UNTITLED_NEXTMOVE_H
#define UNTITLED_NEXTMOVE_H
#include "Logic.h"

//A sub-class that represents a normal logic of the game

class NormalLogic: public Logic{

public:
    /************************************************************************
	* Name: NormalLogic (Default Constructor)
	* Input: b - The board that the logic should be implied on
	* Output: -
	* Operation: Initialize Normal-Logic calculation for the game
	*************************************************************************/
    NormalLogic(Board*& b);
    /************************************************************************
      * Name: Logic (Destructor)
      * Input: -
      * Output: -
      * Operation: Not in use for now
      *************************************************************************/
    ~NormalLogic();

    /************************************************************************
     * Name: helper
     * Input: current - the current Value in the board.
     * player and other - the players.
     * &sawother - tells if other's Value has been seen in the line
     * &need_update - tells if the board should be update (so the player can
     * put a new token)
     * Output: Return true if the loop should break (when see ' ' or player's Value)
     * Operation: Helps each of the 'for' and save code. Also changes the value of
     * &sawOther and &need_update when other player's Value appear and when
     * ' ' appears.
     *************************************************************************/
    bool shouldStop(const Value &current, const Value &player,
                    const Value &other, bool &sawOther, bool &need_update) const;

    /************************************************************************
      * Name: flipHelper
      * Input: current - the current Value on the board
      * player - the player
      * hasSame - bool that checks if there's a token in this line that is same
      * as the player's token
      * Output: Return true if the loop should break (when see ' ' or player's Value)
      * Operation: Helps the flip to decide if the line should be flipped
      *************************************************************************/
    bool flipHelper(const Value &current, const Value &player, bool &hasSame) const;

    void setAvailableMoves(set<Coordinate> &availableMoves);

    //All of the other funcs were described in Logic class
    virtual void calculate(Coordinate &c, const Value &player);
    virtual set<Coordinate> availableMoves(const Value token);
    virtual bool isLegal(Coordinate &c) const;
    virtual void flip(Coordinate c, const Value &player);
    virtual void setCurrentBoard(Board * b);
    virtual void makeMove(Coordinate &c, Value v, Board * b);
};


#endif //UNTITLED_NEXTMOVE_H
