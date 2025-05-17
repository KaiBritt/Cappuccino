cmake_minimum_required(VERSION 3.28)
project(engine)

set(CMAKE_CXX_STANDARD 17)

add_executable(engine
        include/Single_node_evaluation.hpp
        include/endgame_piecetables.hpp
        include/middlegame_piecetables.hpp
        include/Board.hpp
        include/Moves.hpp
        src/Single_node_evaluation.cpp
        src/main.cpp
        src/Board.cpp
        src/Moves.cpp
#        voronoi.cpp
#        voronoi.h
        src/minimax.cpp
        include/minimax.h
        src/UCI.cpp
        include/UCI.hpp
)

#add_executable(voronoibb voronoiStandalone.cpp voronoi.h)

#target_link_libraries(engine)

#target_link_libraries(voronoibb PRIVATE gmp gmpxx mpfr)
