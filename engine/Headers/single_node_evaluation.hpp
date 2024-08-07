//
// Created by cinna on 06/08/24.
//

#ifndef SINGLE_NODE_EVALUATION_HPP
#define SINGLE_NODE_EVALUATION_HPP
#define ULL unsigned long long
#define PAWN 100
#define KNIGHT 300
#define BISHOP 320
#define ROOK 500
#define QUEEN 900
#define KING 20000
#include <array>
#include "endgame_piecetables.hpp"
#include "middlegame_piecetables.hpp"

struct piece_values
{
    int whitePieceTotal;
    int blackPieceTotal;
    int totalPieceEval;
};

int flip_square(int index);
int evaluate_node();
piece_values evaluate_piece_values(const std::array<int,64>& board);
std::array<int,64> adjust_positional_values(const std::array<int,64>& board);

#endif //SINGLE_NODE_EVALUATION_HPP
