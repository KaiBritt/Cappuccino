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
#include <unordered_map>

#include "Global.hpp"

typedef struct{
    int startPos;
    int endPos;

    bool isCastle;
    bool isEnPassant;
} move;

std::list<move> get_moves(std::map<int, ULL> pieceBitBoards); 
ULL enemy_or_empty();
std::array<std::unordered_map<int, ULL>, 64> generate_lookup_table();


ULL find_rook_legal_moves(int position, ULL blockers) ;
std::unordered_map<ULL, ULL> generate_blocker_map(int position, ULL movement_map, ULL (*find_legal_moves)(int,ULL) );
std::array<std::unordered_map<int, std::unordered_map<ULL,ULL>>, 64>blocker_lookup_table( std::array<std::unordered_map<int, ULL>, 64> movement_lookup_table);
void store_lookup_tables(std::array<std::unordered_map<int, ULL>, 64> tables);
std::array<std::unordered_map<int, ULL>, 64> load_lookup_tables();

std::string md5(const std::string &str);
bool validate_lookup_table();

ULL swap_bytes_vertically(ULL original);

#endif