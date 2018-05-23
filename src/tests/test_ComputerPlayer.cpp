#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "ComputerTest.h"
#include "../client/include/Printer.h"
#include "../client/include/ConsolePrinter.h"

TEST_F(ComputerTest, DoMove) {
    //Printer *printer = new ConsolePrinter();
    cout << "Here\n";
    printer->massage("amir\n");

    board->update(Coordinate(2,3), Black);
    logic->flip(Coordinate(2,3), Black);
    cout << "Here1\n";
    set<Coordinate> availableMoves = logic->availableMoves(White);
    printer->availableMoves(availableMoves);
    cout << "Here2\n";
    Coordinate makedMove(player.makeTurn(logic,board,availableMoves));
    cout << "Here3\n";
/* The Current Board will be like this
    | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
    -----------------------------------
  1 |   |   |   |   |   |   |   |   |
    -----------------------------------
  2 |   |   |   |   |   |   |   |   |
    -----------------------------------
  3 |   |   |   | X |   |   |   |   |
    -----------------------------------
  4 |   |   |   | X | X |   |   |   |
    -----------------------------------
  5 |   |   |   | X | O |   |   |   |
    -----------------------------------
  6 |   |   |   |   |   |   |   |   |
    -----------------------------------
  7 |   |   |   |   |   |   |   |   |
    -----------------------------------
  8 |   |   |   |   |   |   |   |   |
   -----------------------------------
  The expected move is (3,3) [which is (2,2)], because it will be the first choose to give
  the most potential-score.
  */
    EXPECT_EQ(Coordinate(2,2), makedMove);

    board->update(makedMove, White);
    logic->flip(makedMove, White);
    logic-> endTurn();

    board->update(Coordinate(2,1), Black);
    logic->flip(Coordinate(2,1), Black);
    availableMoves = logic->availableMoves(White);
    Coordinate anotherMove = player.makeTurn(logic,board, availableMoves);
    EXPECT_EQ(Coordinate(2,4), anotherMove);
}
TEST_F(ComputerTest, OnePlaceOnly) {
    //Clear the board
    board->update(Coordinate(2, 3), Empty);
    board->update(Coordinate(3, 2), Empty);
    board->update(Coordinate(4, 5), Empty);
    board->update(Coordinate(5, 4), Empty);

    //Make the computer have only one option to move
    board->update(Coordinate(2, 3), Black);
    board->update(Coordinate(2, 2), White);
    set<Coordinate> availableMoves = logic->availableMoves(White);
    Coordinate makedMove(player.makeTurn(logic, board, availableMoves));
    EXPECT_EQ(Coordinate(2,4), makedMove);
}