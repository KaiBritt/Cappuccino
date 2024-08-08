//
// Created by elmo on 07/08/24.
//

#ifndef MOVES_HPP
#define MOVES_HPP
#define ULL unsigned long long
#define PAWN 100
#define KNIGHT 300
#define BISHOP 320
#define ROOK 500
#define QUEEN 900
#define KING 20000
#include <fstream>
#include <string>
#include <iomanip>

struct move{
    int startIndex;
    int endIndex;
    int promotionType;
    int castleSide;
};

std::list<move> get_moves(std::map<int, ULL> pieceBitBoards);

std::array<std::map<int, ULL>, 64> generate_lookup_table();

void store_lookup_tables(std::array<std::map<int, ULL>, 64> tables);
std::array<std::map<int, ULL>, 64> load_lookup_tables();

std::string md5(const std::string &str);
bool validate_lookup_table();

void print_bit_board(ULL bitboard);
#endif