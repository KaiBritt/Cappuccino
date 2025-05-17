//
// Created by cinna on 06/08/24.
//

#ifndef SINGLE_NODE_EVALUATION_HPP
#define SINGLE_NODE_EVALUATION_HPP
#include "Board.hpp"
#include "Global.hpp"
#include "endgame_piecetables.hpp"
#include "middlegame_piecetables.hpp"

struct evaluations
{
    int mgEvaluation;
    int egEvaluation;
};
constexpr int pPhase = 0;
constexpr int nPhase = 1;
constexpr int bPhase = 1;
constexpr int rPhase = 2;
constexpr int qPhase = 4;

int flip_square(int index);
int evaluate_node(const std::array<int,64>& board);
int calculate_phase(const std::array<int,64>& board);
int evaluate_node_VD(Board board);
evaluations evaluate_piece_values(const std::array<int,64>& board);

#endif //SINGLE_NODE_EVALUATION_HPP
