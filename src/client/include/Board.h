
#ifndef REVERSI_BOARD_H
#define REVERSI_BOARD_H


#include "Cell.h"


class Board {
private:
    Cell*** board; // The board
    const int size; //The board's size
    const Value p1Token;
    const Value p2Token;
public:
    /*************************************************************************
    * Name: Board (Constructor)
    * Input: size - the size of the board
    * Output: -
    * Operation: The function build a board with the size from input
    *************************************************************************/
    Board(const int &size, const Value &p1Token, const Value &p2Token);

    //Copy constructor
    Board(Board*& b);

    /*************************************************************************
    * Name: ~Board (Destructor)
    * Input: -
    * Output: -
    * Operation: The function frees the allocated memory for the board.
    *************************************************************************/
    ~Board();

    /*************************************************************************
    * Name: Initialize
    * Input: size - the size of the board
    * Output: -
    * Operation: The function Initialize the board with ' ','O','X' on the
    * right places.
    *************************************************************************/
    void initialize();

    /*************************************************************************
    * Name: Update
    * Input: (row, col) or Coordinate, and the token of the player
    * Output: -
    * Operation: The function updates a new piece/token on the board
    *************************************************************************/
    void update(const int &row, const int &col, const Value &player);
    void update(Coordinate c, const Value &player);

    /*************************************************************************
    * Name: GetSize
    * Input: -
    * Output: Returns the size
    * Operation: "      "   "
    *************************************************************************/
    const int getSize() const;
    /*************************************************************************
    * Name: GetValue
    * Input: row and col of spesific cell
    * Output: Returns the value of the Value in the cell
    * Operation: "      "   "
    *************************************************************************/
    Value getValue(const int &row, const int &col) const;

    /*************************************************************************
    * Name: StartMode
    * Input: players tokens
    * Output: -
    * Operation: Set the board as the start of the game (4 tokens on middle)
    *************************************************************************/
    void startMode(const Value &p1Token,const Value &p2Token) const;

    /*************************************************************************
    * Name: Clear
    * Input: -
    * Output: -
    * Operation: Clears the board (all cells are ' ')
    *************************************************************************/
    void clear() const;

    /*************************************************************************
    * Name: IsFull
    * Input: -
    * Output: -
    * Operation: Returns if the board is full
    *************************************************************************/
    bool isFull() const;

    //Operator = for copying board
    Board &operator =(const Board &board);

    /*************************************************************************
    * Name: score
    * Input: value of player
    * Output: it's score with compare to other player
    * Operation:
    *************************************************************************/
    int score(Value player);
    //Return p1 Value
    const Value getp1();
    //Return p2 Value
    const Value getp2();
    //Return the other player Value
    const Value getOpponent(const Value x);
    //Return the last played move
    Coordinate getLastMoved();

};


#endif //REVERSI_BOARD_H