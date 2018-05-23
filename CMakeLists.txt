cmake_minimum_required(VERSION 3.8)
project(Reversi)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpthread")
set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++98 -pthread")

add_subdirectory(src/lib/google_tests)
include_directories(src/lib/google_tests/googletest/include)
include_directories(src/lib/google_tests/googlemock/include)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(TEST_FILES src/tests/main_test.cpp src/tests/test_Board.cpp src/tests/test_NormalLogic.cpp
        src/tests/test_ComputerPlayer.cpp src/tests/test_Coordinate.cpp src/tests/LogicTest.h src/tests/BoardTest.h src/tests/ComputerTest.h)

set(SOURCE_FILES src/client/srcReversi/Board.cpp
        src/client/include/Board.h
        src/client/srcReversi/Cell.cpp
        src/client/include/Cell.h

        src/client/srcReversi/Client.cpp
        src/client/include/Client.h
        src/client/srcReversi/RemotePlayer.cpp
        src/client/include/RemotePlayer.h

        src/client/srcReversi/Cell.cpp
        src/client/include/Cell.h
        src/client/srcReversi/ConsolePrinter.cpp
        src/client/include/ConsolePrinter.h
        src/client/srcReversi/GameManager.cpp
        src/client/include/GameManager.h
        src/client/srcReversi/HumanPlayer.cpp
        src/client/include/HumanPlayer.h
        src/client/srcReversi/Logic.cpp
        src/client/include/Logic.h
        src/client/srcReversi/NormalLogic.cpp
        src/client/include/NormalLogic.h
        src/client/srcReversi/Coordinate.cpp
        src/client/include/Coordinate.h
        src/client/srcReversi/Player.cpp
        src/client/include/Player.h
        src/client/srcReversi/Printer.cpp
        src/client/include/Printer.h
        src/client/srcReversi/ComputerPlayer.cpp
        src/client/include/ComputerPlayer.h
        src/server/Server.cpp
        src/server/Server.h
        src/server/Command.h src/server/CommandManager.cpp src/server/CommandManager.h
        src/server/StartCommand.cpp src/server/StartCommand.h
        src/server/GameInfo.cpp src/server/GameInfo.h
        src/server/ClientHandler.cpp
        src/server/ClientHandler.h src/server/GamesListCommand.cpp
        src/server/GamesListCommand.h src/server/JoinCommand.cpp
        src/server/JoinCommand.h src/server/Task.cpp src/server/Task.h src/server/ThreadPool.cpp src/server/ThreadPool.h)

add_executable(Reversi ${SOURCE_FILES} src/client/srcReversi/main.cpp)
add_executable(server ${SOURCE_FILES} src/server/main.cpp)
add_executable(TestGame  ${SOURCE_FILES} ${TEST_FILES} src/tests/main_test.cpp)
target_link_libraries(TestGame gtest gtest_main pthread)








