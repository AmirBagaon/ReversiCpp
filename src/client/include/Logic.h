//
// Created by amir on 02/11/17.
//

#ifndef REVERSI_LOGIC_H
#define REVERSI_LOGIC_H
#include "Board.h"
#include "Coordinate.h"
#include "Printer.h"
#include <set>
using namespace std;

//A super class that represents the logic of the game

class Logic {

protected:
    Board* board; // The Board
    int size; // The size of the board
    set<Coordinate> canMove;
    Coordinate last;
public:
    /************************************************************************
	* Name: Logic (Default Constructor)
	* Input: b - The board that the logic should be implied on
	* Output: -
	* Operation: Initialize the logic (rules) calculation of the game
	*************************************************************************/
    Logic(Board*& b);

    /************************************************************************
    * Name: ~Logic (Destructor)
    * Input: -
    * Output: -
    * Operation: Frees the allocated memory for the temp board
    *************************************************************************/
    virtual ~Logic();

    /************************************************************************
	* Name: Calculate
	* Input: row and col of spesific cell, and the current player
	* Output: -
	* Operation: Calculates the possible moves for spesific cell
	*************************************************************************/
    virtual void calculate(Coordinate &c, const Value &player) = 0;

    /************************************************************************
	* Name: CalculateAll
	* Input: Current player
	* Output: -
	* Operation: Calculates the whole possible moves for a player
	*************************************************************************/
    virtual void calculateAll(const Value &player1);
    //Return the last played move
    virtual Coordinate getLastMove();
    virtual void couldntMove();

        /************************************************************************
        * Name: availableMoves
        * Input: -
        * Output: -
        * Operation: Calculate and print the legal moves for a player, if any.
        *************************************************************************/
    virtual set<Coordinate> availableMoves(const Value token) = 0;

    /************************************************************************
	* Name: IsLegal
	* Input: Coordinate &c - input from the player for a move
	* Output: -
	* Operation: Returns if the input for the move is legal
	*************************************************************************/
    virtual bool isLegal(Coordinate &c) const = 0;

    /************************************************************************
	* Name: Flip
	* Input: row and col on the board and the current player
	* Output: -
	* Operation: Flips all the appropriate tokens after the player putted
    * a token.
	*************************************************************************/
    virtual void flip(Coordinate c, const Value &player) = 0;

    /************************************************************************
    * Name: EndTurn
    * Input:=
    * Output: -
    * Operation: Clears the temp board for a new use
    *************************************************************************/
    virtual void endTurn();

    /************************************************************************
    * Name: setAvailableMoves
    * Input: set of coordinates
    * Output: -
    * Operation: Get a set of coordinate and change the current logic's set
    * to it
    *************************************************************************/
    virtual void setAvailableMoves(set<Coordinate> &availableMoves) = 0;
    /************************************************************************
    * Name: setCurrentBoard
    * Input: pointer of a board
    * Output: -
    * Operation: Make the logic to work on the input board
    *************************************************************************/
    virtual void setCurrentBoard(Board * b) = 0;

    virtual void makeMove(Coordinate &c, Value v, Board * b) = 0;
};


#endif //REVERSI_LOGIC_H
