//
// Created by kai on 8/6/24.
//

#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "Global.hpp"
#include  "Moves.hpp"


class Board
{
public:
    explicit Board(const char * FEN);
    unsigned long long bitboards[14]; //index of specific bitboards: 0 = black; 1 = p; 2 = r; 3 = n; 4 = b; 5 = q; 6 = k; 7 = white; 8 = p; 9 = r; 10 = n; 11 = b; 12 = q; 13 = k;
    std::array<int,64> letterbox;
    // std::vector<move> game_moves;
    std::vector<int> en_passant_list;
    void make_move(Move* move);
    void unmake_move(Move* move);

private:
    std::map<char,int> m{{'D', 0}, {'p', 1}, {'r', 2}, {'n', 3}, {'b', 4}, {'q', 5}, {'k', 6}, {'W', 7}, {'P', 8}, {'R', 9}, {'N', 10}, {'B', 11}, {'Q', 12}, {'K', 13}};
};

void print_bit_board(unsigned long long bitboard);
void print_letterbox(const std::array<int,64> &letterbox);


#endif
