//
// Created by cinna on 06/08/24.
//

#ifndef SINGLE_NODE_EVALUATION_HPP
#define SINGLE_NODE_EVALUATION_HPP
#include "Global.hpp"
#include "endgame_piecetables.hpp"
#include "middlegame_piecetables.hpp"

struct piece_values
{
    int whitePieceTotal;
    int blackPieceTotal;
    int totalPieceEval;
};

inline bool endgame = false;
int flip_square(int index);
int evaluate_node(const std::array<int,64>& board);
piece_values evaluate_piece_values(const std::array<int,64>& board);

#endif //SINGLE_NODE_EVALUATION_HPP
