//
// Created by amir on 25/10/17.
//



#include <iostream>
#include "../include/Board.h"
#include "../include/NormalLogic.h"

using namespace std;
NormalLogic::NormalLogic(Board*& b): Logic(b) {

}
NormalLogic::~NormalLogic() {
}

bool NormalLogic::shouldStop(const Value &current, const Value &player,
                             const Value &other, bool &sawOther, bool &need_update) const{
    if (current == other) {
        sawOther = true;
        return false;
    }
    if (current == ' ') {
        if (sawOther) {
            need_update = true;
        }
    }
    //In case of ' ' or player's Value
    return true;
}
void NormalLogic::calculate(Coordinate &c, const Value &player) {
    int row = c.getRow();
    int col = c.getCol();
    Value current;
    Value other = board->getOpponent(player);
    bool sawOther = false;
    bool need_update = false;

    //Down
    int i;
    for (i = row + 1; i < size; i ++) {
        current = board->getValue(i, col);
        if (shouldStop(current, player, other, sawOther, need_update)) {
            break;
        }
    }
    if (need_update) {
        canMove.insert(Coordinate(i, col));
    }

    //Right
    sawOther = need_update = false;

    for (i = col + 1; i < size; i ++) {
        current = board->getValue(row, i);
        if (shouldStop(current, player, other, sawOther, need_update)) {
            break;
        }
    }
    if (need_update) {
        canMove.insert(Coordinate(row, i));
    }

    //Left
    sawOther = need_update = false;

    for (i = col - 1; i >= 0; i--) {
        current = board->getValue(row, i);
        if (shouldStop(current, player, other, sawOther, need_update)) {
            break;
        }
    }
    if (need_update) {
        canMove.insert(Coordinate(row, i));
    }

    //Up
    sawOther = need_update = false;

    for (i = row - 1; i  >= 0; i --) {
        current = board->getValue(i, col);
        if (shouldStop(current, player, other, sawOther, need_update)) {
            break;
        }
    }
    if (need_update) {
        canMove.insert(Coordinate(i, col));
    }

    //Down-right
    int temp_row = row + 1;
    sawOther = need_update = false;

    for (i = col + 1; i < size && temp_row < size; i++, temp_row++) {
        current = board->getValue(temp_row, i);
        if (shouldStop(current, player, other, sawOther, need_update)) {
            break;
        }
    }
    if (need_update) {
        canMove.insert(Coordinate(temp_row, i));
    }

    //Up-right
    temp_row = row - 1;
    sawOther = need_update = false;

    for (i = col + 1; i < size && temp_row >= 0; i++, temp_row--) {
        current = board->getValue(temp_row, i);
        if (shouldStop(current, player, other, sawOther, need_update)) {
            break;
        }
    }
    if (need_update) {
        canMove.insert(Coordinate(temp_row, i));
    }
    //Up-left
    temp_row = row - 1;
    sawOther = need_update = false;

    for (i = col - 1; i >= 0 && temp_row >= 0; i--, temp_row--) {
        current = board->getValue(temp_row, i);
        if (shouldStop(current, player, other, sawOther, need_update)) {
            break;
        }
    }
    if (need_update) {
        canMove.insert(Coordinate(temp_row, i));
    }

    //Down-left
    temp_row = row + 1;
    sawOther = need_update = false;

    for (i = col - 1; i >= 0 && temp_row < size; i--, temp_row++) {
        current = board->getValue(temp_row, i);
        if (shouldStop(current, player, other, sawOther, need_update)) {
            break;
        }
    }
    if (need_update) {
        canMove.insert(Coordinate(temp_row, i));
    }
}

set<Coordinate> NormalLogic::availableMoves(const Value token){
    calculateAll(token);
    return canMove;
}
bool NormalLogic::isLegal(Coordinate &c) const{
    int row = c.getRow();
    int col = c.getCol();
    if ((row >= size) || (col >= size)) {
        return false;
    }

    Coordinate coordinate(row, col);

    //Check if it is not a move from the avaliable moves
    const bool is_in = canMove.find(coordinate) != canMove.end();
    if (!is_in) {
        return false;
    }
    return true;
}

bool NormalLogic::flipHelper(const Value &current, const Value &player, bool &hasSame) const{
    if((current != player) && (current != ' ')) {
        return false;
    }
    if (current == player) {
        hasSame = true;
    }
    return true;
}

void NormalLogic::flip(Coordinate c, const Value &player) {

    int row = c.getRow();
    int col = c.getCol();

    bool hasSame = false;
    Value current;
    int i, j, k;

    //Right
    for (i = col + 1; i < size; i++) {
        current = board->getValue(row, i);
        if (flipHelper(current, player, hasSame)) {
            break;
        }
    }
    if (hasSame) {
        for (j = col + 1; j <= i; j++) {
            board->update(row, j, player);
        }
    }

    //Left
    hasSame = false;
    for (i = col - 1; i >= 0; i--) {
        current = board->getValue(row, i);
        if (flipHelper(current, player, hasSame)) {
            break;
        }
    }
    if (hasSame) {
        for (j = col - 1; j >= i; j--) {
            board->update(row, j, player);
        }
    }
    //Down
    hasSame = false;
    for (i = row + 1; i < size; i++) {
        current = board->getValue(i, col);
        if (flipHelper(current, player, hasSame)) {
            break;
        }
    }
    if (hasSame) {
        for (j = row + 1; j <= i; j++) {
            board->update(j, col, player);
        }
    }

    //Up
    hasSame = false;
    for (i = row - 1; i >= 0; i--) {
        current = board->getValue(i, col);
        if (flipHelper(current, player, hasSame)) {
            break;
        }
    }
    if (hasSame) {
        for (j = row - 1; j >= i; j--) {
            board->update(j, col, player);
        }
    }

    //Down-Right
    int temp_row;
    hasSame = false;
    for (i = col + 1, temp_row = row + 1; i < size && temp_row < size; i++, temp_row++) {
        current = board->getValue(temp_row, i);
        if (flipHelper(current, player, hasSame)) {
            break;
        }
    }
    if (hasSame) {
        for (j = col + 1, k = row + 1; j <= i, k <= temp_row; j++, k++) {
            board->update(k, j, player);
        }
    }

    //Up-Right
    hasSame = false;
    for (i = col + 1, temp_row = row - 1; i < size && temp_row >= 0; i++, temp_row--) {
        current = board->getValue(temp_row, i);
        if (flipHelper(current, player, hasSame)) {
            break;
        }
    }
    if (hasSame) {
        for (j = col + 1, k = row - 1; j <= i, k >= temp_row; j++, k--) {
            board->update(k, j, player);
        }
    }

    //Up-Left
    hasSame = false;
    for (i = col - 1, temp_row = row - 1; i >= 0 && temp_row >= 0; i--, temp_row--) {
        current = board->getValue(temp_row, i);
        if (flipHelper(current, player, hasSame)) {
            break;
        }
    }
    if (hasSame) {
        for (j = col - 1, k = row - 1; j >= i, k >= temp_row; j--, k--) {
            board->update(k, j, player);
        }
    }

    //Down-Left
    hasSame = false;
    for (i = col - 1, temp_row = row + 1; i >= 0 && temp_row < size; i--, temp_row++) {
        current = board->getValue(temp_row, i);
        if (flipHelper(current, player, hasSame)) {
            break;
        }
    }
    if (hasSame) {
        for (j = col - 1, k = row + 1; j >= i, k <= temp_row; j--, k++) {
            board->update(k, j, player);
        }
    }
}

void NormalLogic::setAvailableMoves(set<Coordinate> &availableMoves) {
    canMove = availableMoves;
}

void NormalLogic::setCurrentBoard(Board *b) {
    board = b;
    size = b->getSize();
}

void NormalLogic::makeMove(Coordinate &position, Value token, Board * b){
    board->update(position, token); //update this one token
    flip(position, token); // flip other tokens
    last = position;
}