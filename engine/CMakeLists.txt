cmake_minimum_required(VERSION 3.28)
project(engine)

set(CMAKE_CXX_STANDARD 17)

add_executable(engine main.cpp
        single_node_evaluation.cpp
        Headers/single_node_evaluation.hpp
        Headers/endgame_piecetables.hpp
        Headers/middlegame_piecetables.hpp
        Headers/Board.hpp
        Board.cpp
)
