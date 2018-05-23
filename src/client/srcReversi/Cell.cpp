//
// Created by or on 01/11/17.
//


#include "../include/Cell.h"

/**
 * constructor.
 * @param x - x value
 * @param y - y value
 * @param s - sign of cell
 */
Cell::Cell(int x, int y, Value s) : coordinate(x,y), sign(s)
{}

bool Cell::isEmpty() const {
    return sign == Empty;
    }

Value Cell::getSign() const {
    return sign;
}

void Cell::setSign(Value newSign) {
    sign = newSign;
}
