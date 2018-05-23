//
// Created by amir on 07/11/17.
//

#ifndef REVERSI_PRINTER_H
#define REVERSI_PRINTER_H

#include <iostream>
#include <set>
#include "Coordinate.h"
#include "Board.h"

using namespace std;

class Printer {
public:
    //Print the board
    virtual void printBoard(Board * board) const = 0;
    //Print the input string
    virtual void massage(const string &s) const = 0;
    //Print in case player cant move
    virtual void cantMove() const = 0;
    //Print when both players cant move
    virtual void noMoreMoves() const = 0;
    //Print the available moves
    virtual void availableMoves(set<Coordinate> legalMoves) const = 0;
    //Print that it's the input players turn
    virtual void yourTurn(const Value &player) const = 0;
    //Print the Coordinate of the played move
    virtual void playingMove(Value v, Coordinate c) = 0;
    //Prints the winner
    virtual void winner(const Value &p1, const Value &p2, const int &score1,
                        const int &score2) const = 0;
    //Get Int from user. If it's not a number - return false
    virtual bool getInput(int &a) = 0;
    virtual void getInput(string &str) = 0;
    virtual string scanString(int i) = 0;
};


#endif //REVERSI_PRINTER_H
