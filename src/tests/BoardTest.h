//
// Created by amir on 27/11/17.
//

#ifndef REVERSI_BOARDTEST_H
#define REVERSI_BOARDTEST_H

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../client/include/Board.h"

using namespace std;

class BoardTest: public testing::Test {
public:

    BoardTest(): board(Board(8, Black, White)){
    }

    virtual void SetUp() {
        cout << "Setting up" << endl;
    }
    virtual void TearDown() {
        cout << "Tearing down" << endl;
    }

protected:
    Board board;
};


#endif //REVERSI_BOARDTEST_H
