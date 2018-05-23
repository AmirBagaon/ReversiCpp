#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "BoardTest.h"
#include "../client/include/Coordinate.h"
#include "../client/include/Board.h"


//Check that board-update works
TEST_F(BoardTest, CellTest) {
    Coordinate c(5,5);
    board.update(c,Black);
    EXPECT_EQ(board.getValue(5, 5), Black);
    board.update(5, 5, White);
    EXPECT_EQ(board.getValue(5, 5), White);
}

//Check that the starting position works
TEST_F(BoardTest, Starting_postion) {
    EXPECT_EQ(board.getValue(3, 3), White);
    EXPECT_EQ(board.getValue(4, 4), White);
    EXPECT_EQ(board.getValue(3, 4), Black);
    ASSERT_EQ(board.getValue(4, 3), Black);
}

//Checks that the copy constructor works
TEST_F(BoardTest, CopyConstructor) {
    Board* b = new Board(8, Black, White);
    Board b2(b);
    EXPECT_EQ(b2.getValue(3, 3), White);
    EXPECT_EQ(b2.getValue(4, 4), White);
    EXPECT_EQ(b2.getValue(3, 4), Black);
    ASSERT_EQ(b2.getValue(4, 3), Black);
}


