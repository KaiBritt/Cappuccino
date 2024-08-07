//
// Created by cinna on 06/08/24.
//

#include "Headers/single_node_evaluation.hpp"

int evaluate_node() {
    return 0;
}

int flip_square(int index) {
    return (index ^ 56);
}


piece_values evaluate_piece_values(const std::array<int,64>& board) {
    piece_values pieceValues = {0, 0, 0};

    for (const int curPiece : board) {
        // start at one corner of the board and loop through summing up totals
        if (curPiece < 0) {
            pieceValues.blackPieceTotal += curPiece;
        }
        else {
            pieceValues.whitePieceTotal += curPiece;
        }
    }
    pieceValues.totalPieceEval = pieceValues.whitePieceTotal + pieceValues.blackPieceTotal;
    return pieceValues;
}


std::array<int,64> adjust_positional_values(const std::array<int,64>& board) {
    std::array<int,64> outputBoard{};
    // currently it is always the middle game
    std::map<int, std::array<int, 64>> gameStateBoards = mg_piece_tables;

    for (int i = 0; i < 64; i++) {
        // check current piece colour (+ is white - is black):
        if (board[i] > 0) {
            // finds the piece square table and adds the position bonus to the output board
            outputBoard[i] = board[i] + gameStateBoards[board[i]][i];
        }
        else if (board[i] < 0) {
            // does the same as above if statement but uses binary maths to flip the square tables (for black values)
            outputBoard[i] = board[i] - gameStateBoards[-board[i]][flip_square(i)];
        }
        else {
            // final case for an empty square just adding an empty square
            outputBoard[i] = 0;
        }
    }
    return outputBoard;
}
