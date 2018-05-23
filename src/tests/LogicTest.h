//
// Created by amir on 27/11/17.
//

#ifndef REVERSI_LOGICTEST_H
#define REVERSI_LOGICTEST_H
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../client/include/Board.h"
#include "../client/include/NormalLogic.h"

using namespace std;


class LogicTest: public testing::Test {
public:

    LogicTest(){
    }

    virtual void SetUp() {
        cout << "Setting up" << endl;
        board = new Board(8, Black, White);
        logic = new NormalLogic(board);
        availableMoves = logic->availableMoves(Black);
    }
    virtual void TearDown() {
        cout << "Tearing down" << endl;
        delete (board);
        delete(logic);
    }

protected:
    Logic* logic;
    Board* board;
    set<Coordinate> availableMoves;
};



#endif //REVERSI_LOGICTEST_H
