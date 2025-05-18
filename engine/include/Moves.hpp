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
#include <vector>
#include "Global.hpp"


class Board;

using BlockerTableArray = std::array<std::unordered_map<int, std::unordered_map<ULL,ULL>>, 64>;
using LookupTableArray = std::array<std::unordered_map<int, ULL>, 64>;
struct Move {
    int startPos;
    int endPos;

    bool isCastle = false;
    bool isEnPassant = false;
    PieceType pieceTaken;

    PieceType movedPiece;       // What piece moved (useful to restore in undo)
    PieceType promotionResult;  // What it was promoted to (if any), use None if no promotion
    bool wasWhite;              // The side that made the move

    bool operator==(const Move& other) const {
        return startPos == other.startPos &&
               endPos == other.endPos &&
               isCastle == other.isCastle &&
               isEnPassant == other.isEnPassant &&
               pieceTaken == other.pieceTaken &&
               movedPiece == other.movedPiece &&
               promotionResult == other.promotionResult &&
               wasWhite == other.wasWhite;
    }
};

std::vector<Move> get_moves(std::map<int, ULL> pieceBitBoards);
std::pair<std::vector<Move>,std::vector<Move>> get_legal_moves(Board* board);

Move parseMoveStr(std::string& str);
ULL enemy_or_empty();
std::array<std::unordered_map<int, ULL>, 64> generate_lookup_table();
int algToPos(const std::string& alg);

ULL find_rook_legal_moves(int position, ULL blockers) ;
std::unordered_map<ULL, ULL> generate_blocker_map(int position, ULL movement_map, ULL (*find_legal_moves)(int,ULL) );
std::array<std::unordered_map<int, std::unordered_map<ULL,ULL>>, 64>generate_blocker_table( std::array<std::unordered_map<int, ULL>, 64> & movement_lookup_table);
void store_lookup_tables(const std::array<std::unordered_map<int, ULL>, 64>& tables);
void store_blocker_tables(const std::array<std::unordered_map<int, std::unordered_map<unsigned long long, unsigned long long>>, 64> & blocker_table);
std::array<std::unordered_map<int, ULL>, 64> load_lookup_tables();

// std::string md5(const std::string &str);
bool validate_lookup_table();

ULL swap_bytes_vertically(ULL original);

#endif