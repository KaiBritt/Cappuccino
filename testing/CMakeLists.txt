cmake_minimum_required(VERSION 3.28)
project(tests)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(googletest)

add_executable(tests
        ../engine/include/Single_node_evaluation.hpp
        ../engine/include/endgame_piecetables.hpp
        ../engine/include/middlegame_piecetables.hpp
        ../engine/include/Board.hpp
        ../engine/include/Moves.hpp
        ../engine/src/Single_node_evaluation.cpp
        ../engine/src/Board.cpp
        ../engine/src/Moves.cpp
        #        voronoi.cpp
        #        voronoi.h
        ../engine/src/minimax.cpp
        ../engine/include/minimax.h
        ../engine/src/UCI.cpp
        ../engine/include/UCI.hpp
        tests.cpp
)


target_link_libraries(
        tests
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests)

