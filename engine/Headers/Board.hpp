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
    std::string export_FEN();
    unsigned long long bitboards[14]; //index of specific bitboards: 0 = black; 1 = p; 2 = r; 3 = n; 4 = b; 5 = q; 6 = k; 7 = white; 8 = p; 9 = r; 10 = n; 11 = b; 12 = q; 13 = k;
    std::array<int,64> letterbox;
    std::vector<Move> game_moves;
    std::vector<Move> legal_moves;
    int en_passant;
    bool white;
    int half_clock;
    int full_clock;
    bool castling[4] = {}; // initialize to fals
    std::vector<Move> set_legal_moves();
    void make_move(Move* move);
    void undo_move();

private:
    std::map<char,int> m{{'D', 0}, {'p', 1}, {'r', 2}, {'n', 3}, {'b', 4}, {'q', 5}, {'k', 6}, {'W', 7}, {'P', 8}, {'R', 9}, {'N', 10}, {'B', 11}, {'Q', 12}, {'K', 13}};
    std::map<int, char> reverse_m{
        {0, 'D'}, {1, 'p'}, {2, 'r'}, {3, 'n'}, {4, 'b'}, {5, 'q'}, {6, 'k'},
        {7, 'W'}, {8, 'P'}, {9, 'R'}, {10, 'N'}, {11, 'B'}, {12, 'Q'}, {13, 'K'}
    };
};

void print_bit_board(unsigned long long bitboard);
void print_letterbox(const std::array<int,64> &letterbox);
std::string posToAlg(int pos);


#endif
