#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "LogicTest.h"
#include "../client/include/ConsolePrinter.h"

//Test That the available moves get values and not staying empty
TEST_F(LogicTest, HasMoves) {
    EXPECT_EQ(availableMoves.empty(), false);
}
//Test that illegal move will be handle
TEST_F(LogicTest, IsLegalMove) {
    Coordinate c(1,1);
    EXPECT_EQ(logic->isLegal(c), false);
}

//Test that the availableMoves-set contains the real available moves
TEST_F(LogicTest, AvailableMoves) {
    Coordinate c(2,3);
    Coordinate c2(3,2);
    Coordinate c3(4,5);
    Coordinate c4(5,4);
    std::set<Coordinate>::iterator it;
    it = availableMoves.begin();
    EXPECT_EQ((*it), c);
    it++;
    EXPECT_EQ((*it), c2);
    it++;
    EXPECT_EQ((*it), c3);
    it++;
    EXPECT_EQ((*it), c4);
}

//Another test of legal moves, this time contains 1 legal and 1 not
TEST_F(LogicTest, IsLegal) {
    Coordinate c(1,1);
    EXPECT_EQ(logic->isLegal(c), false);
    Coordinate c2(2,3);
    EXPECT_EQ(logic->isLegal(c2), true);
}
TEST_F(LogicTest, NoMoves) {
    //Deleting board and available moves content
    board->update(Coordinate(3, 3), Empty);
    board->update(Coordinate(3, 4), Empty);
    board->update(Coordinate(4, 4), Empty);
    board->update(Coordinate(4, 3), Empty);
    logic->endTurn();
    //Set X So he cant move
    board->update(Coordinate(0, 1), Black);
    board->update(Coordinate(0, 0), White);
    availableMoves = logic->availableMoves(Black);
    EXPECT_EQ(availableMoves.empty(), true);
}
TEST_F(LogicTest, AllDirection) {
    //Deleting board and available moves content
    board->update(Coordinate(3, 3), Empty);
    board->update(Coordinate(3, 4), Empty);
    board->update(Coordinate(4, 4), Empty);
    board->update(Coordinate(4, 3), Empty);
    logic->endTurn();

    /* Make sure that x has 8 options to move
 *   | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
    -----------------------------------
    1 |   |   |   |   |   |   |   |   |
    -----------------------------------
    2 |   |   |   |   |   |   |   |   |
    -----------------------------------
    3 |   |   | O | O | O |   |   |   |
    -----------------------------------
    4 |   |   | O | X | O |   |   |   |
    -----------------------------------
    5 |   |   | O | O | O |   |   |   |
    -----------------------------------
    6 |   |   |   |   |   |   |   |   |
    -----------------------------------
     */

    //Set X So he cant move
    board->update(Coordinate(3, 3), Black);
    board->update(Coordinate(2, 2), White);
    board->update(Coordinate(4, 4), White);
    board->update(Coordinate(3, 2), White);
    board->update(Coordinate(2, 3), White);
    board->update(Coordinate(4, 3), White);
    board->update(Coordinate(3, 4), White);
    board->update(Coordinate(2, 4), White);
    board->update(Coordinate(4, 2), White);
    Printer *p = new ConsolePrinter();
    //p->printBoard(board);
    availableMoves = logic->availableMoves(Black);
    std::set<Coordinate>::iterator it;
    for (it=availableMoves.begin(); it!=availableMoves.end();) {
//        cout << "(" << (*it).getRow() + 1 << "," << (*it).getCol() + 1 << ")";
        // put ','
        if ((++it) != availableMoves.end()) {
  //          cout << ",";
        }
    }

    EXPECT_EQ(availableMoves.size(), 8);
}
TEST_F(LogicTest, Flip) {
    //Deleting board and available moves content
    board->update(Coordinate(3, 3), Empty);
    board->update(Coordinate(3, 4), Empty);
    board->update(Coordinate(4, 4), Empty);
    board->update(Coordinate(4, 3), Empty);
    logic->endTurn();

    //
    for (int i = 0; i < 5; i ++) {
        board->update(Coordinate(1 + i, 1), Black);
        board->update(Coordinate(1, 1 + i), Black);
        board->update(Coordinate(5, 1 + i), Black);
        board->update(Coordinate(1 + i, 5), Black);
    }
    board->update(Coordinate(3, 3), Black);
    board->update(Coordinate(2, 2), White);
    board->update(Coordinate(4, 4), White);
    board->update(Coordinate(3, 2), White);
    board->update(Coordinate(2, 3), White);
    board->update(Coordinate(4, 3), White);
    board->update(Coordinate(3, 4), White);
    board->update(Coordinate(2, 4), White);
    board->update(Coordinate(4, 2), White);
/* Creating a board like this and make sure all of the O will be flipped
| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
-----------------------------------
1 |   |   |   |   |   |   |   |   |
-----------------------------------
2 |   | X | X | X | X | X |   |   |
-----------------------------------
3 |   | X | O | O | O | X |   |   |
-----------------------------------
4 |   | X | O | X | O | X |   |   |
-----------------------------------
5 |   | X | O | O | O | X |   |   |
-----------------------------------
6 |   | X | X | X | X | X |   |   |
-----------------------------------
7 |   |   |   |   |   |   |   |   |
-----------------------------------
8 |   |   |   |   |   |   |   |   |
-----------------------------------
 */
    logic->flip(Coordinate(3,3), Black);
    Printer * p = new ConsolePrinter();
    p->printBoard(board);
    EXPECT_EQ((logic->availableMoves(White)).size(), 0);
}





