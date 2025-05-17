//
// Created by kai on 5/14/25.
//

#ifndef MINIMAX_H
#define MINIMAX_H
#include "Moves.hpp"
#include "Board.hpp"
Move find_best_move(Board *board, int depth) ;
 Move minimax(Board,int depth, int alpha, int beta);



#endif //MINIMAX_H
