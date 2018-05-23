//
// Created by or on 28/11/17.
//

#ifndef REVERSI_CELL_H
#define REVERSI_CELL_H

#include "Coordinate.h"

typedef enum Value {Black = 'X', White = 'O', Empty = ' '} Value;

class Cell
{
public:
    // Constructor
    Cell(int x, int y, Value s);
    //Returns the sign of the Cell
    Value getSign() const ;
    //Set the sign of the Cell
    void setSign(Value newSign);
    //Return if the cell is empty.
    bool isEmpty() const;

private:
    Coordinate coordinate;
    Value sign;
};


#endif //REVERSI_CELL_H
