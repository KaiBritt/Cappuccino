cmake_minimum_required(VERSION 3.28)
project(engine)

set(CMAKE_CXX_STANDARD 17)

add_executable(engine
        Headers/Single_node_evaluation.hpp
        Headers/endgame_piecetables.hpp
        Headers/middlegame_piecetables.hpp
        Headers/Board.hpp
        Headers/Moves.hpp
        Headers/Visualisation.hpp
        Single_node_evaluation.cpp
        main.cpp
        Board.cpp
        Moves.cpp
        Visualisation.cpp

)
