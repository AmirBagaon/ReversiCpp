//
// Created by amir on 02/11/17.
//

#include "../include/Board.h"
#include "../include/Logic.h"

using namespace std;
Logic::Logic(Board*& b) : last(-3, -3) { //The num -3 signs that its the first time
    board = b;
    size = b->getSize();
}

Logic::~Logic() {}

void Logic::calculateAll(const Value &player) {
    for (int row = 0; row < board->getSize(); row++) {
        for (int col = 0; col < board->getSize(); col++) {
            if (board->getValue(row, col) == player) {
                Coordinate coordinate(row,col);
                calculate(coordinate, player);
            }
        }
    }
}

Coordinate Logic::getLastMove() {
    return last;
}
void Logic::couldntMove() {
    last = Coordinate(-2,-2);
}

void Logic::endTurn() {
  //  temp_board->clear();
    canMove.clear();
}
