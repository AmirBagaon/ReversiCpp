//
// Created by amir on 02/11/17.
//

#include <iostream>
#include "../include/ComputerPlayer.h"

using namespace std;
ComputerPlayer::ComputerPlayer(const Value t ,Printer* p): Player(t) ,printer(p) {
}
ComputerPlayer::~ComputerPlayer() {}

Coordinate ComputerPlayer::makeTurn(Logic* logic, Board* originalBoard,
                                    set<Coordinate> availableMoves) {
    printer->availableMoves(availableMoves); // Print available moves

    printer->massage("\nComputer thinking...\n\n");
    Board tempBoard(originalBoard);

//    Board* tempBoard = new Board(originalBoard);
    set<Coordinate> backUp = availableMoves;
    Value opponent = originalBoard->getOpponent(sign);
    logic->setCurrentBoard(&tempBoard);

    int minRow, minCol;
    minRow = minCol = -1;
    int minMaxScore = originalBoard->getSize() * originalBoard->getSize() + 1;


    std::set<Coordinate>::iterator computerIT;
    //Run over each move the computer can do
    for (computerIT=availableMoves.begin(); computerIT!=availableMoves.end(); ++computerIT) {
        int maxScore = originalBoard->getSize() * originalBoard->getSize() * (-1) - 1;
        tempBoard.update((*computerIT), sign); //update this one token
        logic->flip((*computerIT), sign); // flip other tokens
        logic->endTurn(); // erase set

        set<Coordinate> humanMoves = logic->availableMoves(opponent);
        if (humanMoves.empty()) {
         //   printer->printBoard(&tempBoard);
            maxScore = tempBoard.score(opponent);
        }

        std::set<Coordinate>::iterator humanIT;
        for (humanIT=humanMoves.begin(); humanIT!=humanMoves.end(); ++humanIT) { //Run over each move the human can do
            tempBoard.update((*computerIT), sign); //update this one token
            logic->flip((*computerIT), sign); // flip other tokens
            logic->endTurn();
            tempBoard.update((*humanIT), opponent); //update this one token
            logic->flip((*humanIT), opponent); // flip other tokens
            int score = tempBoard.score(opponent);
            if (score > maxScore) {
                maxScore = score;
            }

        }

        if (maxScore < minMaxScore) {
            minMaxScore = maxScore;
            //take the coordianate of the computer player
            minRow = (*computerIT).getRow();
            minCol = (*computerIT).getCol();
        }

//        tempBoard = originalBoard;
        tempBoard = Board(originalBoard);
//        tempBoard.copyBoard(originalBoard);
    }
    logic->setAvailableMoves(backUp);
    logic->setCurrentBoard(originalBoard);
//    delete(tempBoard);
return Coordinate(minRow ,minCol);
}

void ComputerPlayer::startTurn( const Value &val, Coordinate c) const {
    printer->playingMove(val, c);
    printer->yourTurn(sign);
}
void ComputerPlayer::cantMove( Logic* l) const {
    l->couldntMove();
    printer->cantMove(); //print that the player cant move
    char pressAnyKey;
    cin >> pressAnyKey; //wait for user to press any key
}
