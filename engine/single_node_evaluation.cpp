//
// Created by cinna on 06/08/24.
//

#include "Headers/single_node_evaluation.hpp"

int flip_square(int index) {
    return (index ^ 56);
}

int evaluate_node(const std::array<int,64>& board) {
    // calculate total value on the board and compare
    piece_values pieceValues = evaluate_piece_values(board);
    int evaluation = pieceValues.totalPieceEval;
    return evaluation;
}

piece_values evaluate_piece_values(const std::array<int,64>& board) {
    piece_values pieceValues = {0, 0, 0};
    // if gamestate is endgame then use the endgame piece tables otherwise use middle game
    std::map<int, std::array<int, 64>> gameStateBoards = endgame ? eg_piece_tables : mg_piece_tables;
    for (int i = 0; i < 64; i++) {
        if (board[i] > 0) {
            // finds the piece square table and adds the position bonus to the output board
            pieceValues.whitePieceTotal += board[i] + gameStateBoards[board[i]][i];
        }
        else if (board[i] < 0) {
            // does the same as above if statement but uses binary maths to flip the square tables (for black values)
            pieceValues.blackPieceTotal += board[i] - gameStateBoards[-board[i]][flip_square(i)];
        }
    }
    pieceValues.totalPieceEval = pieceValues.whitePieceTotal + pieceValues.blackPieceTotal;
    return pieceValues;
}