#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../client/include/Coordinate.h"

//Check that coordinate constructor works
TEST(CoordinateTest, RegularTest) {
    Coordinate c(5, 7);
    EXPECT_EQ(c.getRow(),5);
    EXPECT_EQ(c.getCol(), 7);

    Coordinate c1(-2, 1);
    EXPECT_EQ(c1.getRow(),-2);
    EXPECT_EQ(c1.getCol(), 1);
}