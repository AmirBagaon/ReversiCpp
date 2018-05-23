
#ifndef REVERSI_COORDINATE_H
#define REVERSI_COORDINATE_H


class Coordinate {
private:
    int row;
    int col;
public:
    //Constructor
    Coordinate(int x1,int y1);
    //Returns the row of the coordinate
    int getRow() const ;
    //Returns the col of the coordinate
    int getCol() const;
    //Operator for ==
    bool operator ==(const Coordinate &other) const;
    //Operator for <
    bool operator <(const Coordinate &other) const;
    Coordinate &operator =(const Coordinate &board);
};


#endif //EX2_COORDINATE_H
