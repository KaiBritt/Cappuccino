//
// Created by kai on 5/14/25.
//

#include "Headers/minimax.h"
#include "Headers/Single_node_evaluation.hpp"


int minimax(Board& board, int depth, int alpha, int beta, bool maximizingPlayer) {

    if (depth == 0) {
        return evaluate_node(board.letterbox);  // Evaluation function (positive = good for White)
    }

    std::vector<Move> moves = get_legal_moves(&board);

    if (maximizingPlayer) {
        int maxEval = -1000000;
        for (Move& move : moves) {
            board.make_move(&move);
            int eval = minimax(board, depth - 1, alpha, beta, false);
            board.undo_move();
            maxEval = std::max(maxEval, eval);
            alpha = std::max(alpha, eval);
            if (beta <= alpha) {
                break;  // Beta cut-off
            }
        }
        return maxEval;
    } else {
        int minEval = 1000000;
        for ( Move& move : moves) {
            board.make_move(&move);
            int eval = minimax(board, depth - 1, alpha, beta, true);
            board.undo_move();
            minEval = std::min(minEval, eval);
            beta = std::min(beta, eval);
            if (beta <= alpha) {
                break;  // Alpha cut-off
            }
        }
        return minEval;
    }
}




Move find_best_move(Board *board, int depth) {
    Move best_move;

    if (board->white){
        int bestScore = -100000000;

        std::vector<Move> moves = get_legal_moves(board);

        for (Move& move : moves) {
            board->make_move(&move);
            int score = minimax(*board, depth-1, -1000000000, 10000000, false);
            board->undo_move();

            if (score > bestScore) {
                bestScore = score;
                best_move = move;
            }
        }
    }
    else {
        int best_score = 1000000000;
        std::vector<Move> moves = get_legal_moves(board);
        for (Move& move : moves) {
            board->make_move(&move);
            int score = minimax(*board, depth-1, -1000000000, 10000000, false);
            board->undo_move();
            if (score < best_score) {
             best_score = score;
             best_move = move;
            }
        }

    }
    return best_move;
}





