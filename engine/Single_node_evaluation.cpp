//
// Created by cinna on 06/08/24.
//

#include "Headers/Single_node_evaluation.hpp"

/// @brief uses binary XOR to flip the square index vertically (e.g. turn a1 into a8)
/// @return int : vertically flipped index
int flip_square(int index) {
    return (index ^ 56);
}


/// @brief evaluates given board using all currently implemented evaluation techniques
/// @return int : single integer number that represents material advantage in centipawns (+100 means white up a pawn)
int evaluate_node(const std::array<int,64>& board) {
    // calculate total value on the board and compare
    evaluations evaluation = evaluate_piece_values(board);
    // calculate game phase for tapered evaluation
    const int phase = calculate_phase(board);

    return (((evaluation.mgEvaluation * (256 - phase)) + (evaluation.egEvaluation * phase)) / 256);
}


/// @brief uses piece square tables to adjust piece values and then sums them up in a total material evaluation
/// @return evaluations : struct consisting of {midGameEval, endGameEval} (allowing for tapered eval)
evaluations evaluate_piece_values(const std::array<int,64>& board) {
    evaluations pieceEvaluations = {0, 0};
    for (int i = 0; i < 64; i++) {
        if (board[i] > 0) {
            // finds the piece square table and adds the position bonus to the output board
            pieceEvaluations.mgEvaluation += (board[i] + mg_piece_tables[board[i]][i]);
            pieceEvaluations.egEvaluation += (board[i] + eg_piece_tables[board[i]][i]);
        }
        else if (board[i] < 0) {
            // does the same as above if statement but uses binary maths to flip the square tables (for black values)
            pieceEvaluations.mgEvaluation += (board[i] - mg_piece_tables[-board[i]][flip_square(i)]);
            pieceEvaluations.egEvaluation += (board[i] - eg_piece_tables[-board[i]][flip_square(i)]);
        }
    }
    return pieceEvaluations;
}


/// @brief calculates game phase (based off tapered eval example at https://www.chessprogramming.org/Tapered_Eval)
/// @return int : gamePhase number used for further evaluation calculations
int calculate_phase(const std::array<int,64>& board) {
    constexpr int totalPhase = pPhase*16 + nPhase*4 + bPhase*4 + rPhase*4 + qPhase*2;
    int phase = totalPhase;
    int wn = 0, wb = 0, wr = 0, wq = 0;
    int bn = 0, bb = 0, br = 0, bq = 0;

    for (const int i : board) {
        // loop over all squares and add up how often each piece appears
        switch (i) {
            case (KNIGHT)  : wn += 1;break;
            case (-KNIGHT) : bn += 1;break;
            case (BISHOP)  : wb += 1;break;
            case (-BISHOP) : bb += 1;break;
            case (ROOK)    : wr += 1;break;
            case (-ROOK)   : br += 1;break;
            case (QUEEN)   : wq += 1;break;
            case (-QUEEN)  : bq += 1;break;
            default        : break;
        }
    }
    phase -= ((wn * nPhase) + (wb * bPhase) + (wr * rPhase) + (wq * qPhase) +
        (bn * nPhase) + (bb * bPhase) + (br * rPhase) + (bq * qPhase));
    return (phase * 256 + (totalPhase / 2)) / totalPhase;
}