//
// Created by amir on 07/11/17.
//

#ifndef REVERSI_CONSOLEPRINTER_H
#define REVERSI_CONSOLEPRINTER_H


#include "Printer.h"

class ConsolePrinter : public Printer {
public:
    //All of them were described at Printer.h
    virtual void printBoard(Board * board) const;
    virtual void cantMove() const;
    virtual void massage(const string &s) const;
    virtual void noMoreMoves() const;
    virtual void availableMoves(set<Coordinate> legalMoves) const;
    virtual void yourTurn(const Value &player) const;
    virtual void winner(const Value &p1, const Value &p2, const int &score1,
                        const int &score2) const;
    virtual void playingMove(Value sign, Coordinate c);
    virtual bool getInput(int &a);
    virtual void getInput(string &str);
    virtual string scanString(int i) ;

//    virtual void getInput(char[] str);
};


#endif //REVERSI_CONSOLEPRINTER_H
