#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "LogicTest.h"

GTEST_API_ int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
