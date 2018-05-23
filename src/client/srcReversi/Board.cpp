
//A Class that represents the game's Board
#include <iostream>
#include "../include/Board.h"

using namespace std;

//Constructor
Board::Board(const int &s, const Value &p1, const Value &p2): size(s), p1Token(p1), p2Token(p2){
    initialize();
    startMode(p1Token, p2Token);

}
Board::Board(Board*& b1): p1Token(b1->getp1()),p2Token(b1->getp2()),
                          size(b1->getSize()){
    board = new Cell**[size]; // size-times array of cells
    for (int i = 0; i < size; i++) {
        board[i] = new Cell*[size]; //each array is size's-cells
    }
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            board[i][j] = new Cell(i, j, b1->getValue(i,j)); // each
        }
    }

}

Board &Board::operator=(const Board &other) {
        if (this != &other) {
            for (int i = 0; i < other.getSize(); i++) {
                for (int j = 0; j < other.getSize(); j++) {
                    board[i][j]->setSign(other.getValue(i, j));
                }
            }
            return *this;
        }
    }

const Value Board::getp1() {
    return p1Token;
}
const Value Board::getp2() {
    return p2Token;
}
const Value Board::getOpponent(const Value x) {
    return p1Token == x? p2Token: p1Token;
}

//Initializes the board
void Board::initialize() {
    //Allocates a 2d matrix
    board = new Cell**[size]; // size-times array of cells
    for (int i = 0; i < size; i++) {
        board[i] = new Cell*[size]; //each array is size's-cells
    }
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            board[i][j] = new Cell(i, j, Empty); // each
        }
    }
}
const int Board::getSize() const{
    return size;
}

void Board::clear() const{
    //Set empty cells
    for (int x = 0;x < size;x++) {
        for(int y = 0;y < size;y++) {
            board[x][y]->setSign(Empty);
        }
    }
}

//Put tokens at start
void Board::startMode(const Value &p1Token,const Value &p2Token) const{
    board[(size / 2) - 1][(size / 2) - 1]->setSign(p2Token);
    board[size / 2][size / 2]->setSign(p2Token);
    board[(size / 2) - 1][size / 2]->setSign(p1Token);
    board[size / 2][(size / 2) - 1]->setSign(p1Token);
}
//Updates the board
void Board::update(const int &row, const int &col, const Value &player) {
    board[row][col]->setSign(player);
}
//Updates the board by coordinate
void Board::update(Coordinate c, const Value &player) {
    board[c.getRow()][c.getCol()]->setSign(player);
 }


//Frees the board's allocation
    Board::~Board() {
    for (int x = 0;x < size;x++) {
        for (int y = 0; y < size; y++) {
            delete board[x][y];
        }
    }
    for (int i = 0; i < size; i++) {
        delete[] board[i];
    }
    delete[] board;
}
//Returns the board
Value Board::getValue(const int &row, const int &col) const{
    return board[row][col]->getSign();
}

//Returns if the board is full
bool Board::isFull() const{
    for (int row = 0;row < size;row++) {
        for(int col = 0;col < size;col++) {
            if (board[row][col]->isEmpty()) {
                return false;
            }
        }
    }
    return true;
}

int Board::score(Value player) {
    Value opponent = getOpponent(player);
    int score = 0;
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            Value val = board[row][col]->getSign();
            if (val == player) {
                score++;
            } else if (val == opponent) {
                score--;
            }
        }
    }
    return score;
}
