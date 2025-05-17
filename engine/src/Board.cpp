//
// Created by kai on 8/6/24.
//

#include "../include/Board.hpp"

#include <optional>
// #include <CGAL/Sqrt_extension/Sqrt_extension_type.h>

/**
* @brief given ull print binary in rows of 8
* @param bitboard number to print
*/
void print_bit_board(unsigned long long bitboard) {
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            unsigned long long two_to_63 = 9223372036854775808UL;
            if ((bitboard & (two_to_63 >> (row*8 + col))) != 0) {
                printf("1");
            }
            else {
                printf("0");
            }
        }
        printf("\n");
    }
    printf("\n");

}

/**
* @brief display letter box board
* @param letter box
**/
void print_letterbox(const std::array<int,64>& letterbox) {
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
          printf("%d ", pointToPiece[letterbox[row*8 + col]]);
        }
        printf("\n");
    }
}
std::vector<std::string> splitFEN(const char* FEN) {
    std::vector<std::string> fields;
    std::string current;
    for (int i = 0; FEN[i] != '\0'; ++i) {
        if (FEN[i] == ' ') {
            if (!current.empty()) {
                fields.push_back(current);
                current.clear();
            }
        } else {
            current += FEN[i];
        }
    }
    if (!current.empty()) {
        fields.push_back(current);
    }
    return fields;
}
/*
* @brief given Forsyth-Edwards Notation (FEN) construct a board
*/
Board::Board(const char * FEN) { // assumes valid FEN
    //making bitboards first
    std::vector<std::string> FenParts = splitFEN(FEN);
    const char *positions = FenParts[0].c_str(); // using c str since im using old code should re write at somepoint *sigh*
    for (unsigned long long & bitboard : bitboards) {
        bitboard = 0;
    }
    int row = 0;
    int col = 0;

    int FEN_size = 0;
    while (positions[FEN_size] != '\0') {
        FEN_size++;
    }
    for (int cc = 0; cc < FEN_size; cc++){

            if (positions[cc] == '/') {
                row+=1;
                col = 0;
            }
            else if ((1 <= (positions[cc] - '0')) and ((positions[cc] -'0') <= 9)){
                col += (positions[cc] - '0');
            }
            else {
                int offset = row * 8 + col;
                bitboards[m[positions[cc]]] = bitboards[m[positions[cc]]] | (1UL<<(63 - offset));
                col += 1;
            }
        }

    //making black and white bitboardss
    for (int i = 1; i < 7; i++) {
        bitboards[m['D']] |= bitboards[m['D'] + i];
        bitboards[m['W']] |= bitboards[m['W'] + i];
     }

    //making evaluation-readable
    char charMap[15] = "DprnbqkWPRNBQK";
    for (int & val : letterbox) {
        val = 0;
    }
    for (int i =0; i < 14; i++) {
        for (int j = 0; j < 64; j++) {
            unsigned long long val = bitboards[i] & (1UL << (63 - j));
            if (val != 0UL) {
                letterbox[j] = charToPoint[charMap[i]];
            }
        }

    }

    std::string turnstr = FenParts[1];
    if (turnstr == "w") {
        white = true; // white
    }
    else {
        white = false; // black
    }

    for (char i : FenParts[2]) {
        if (i == 'K') {
            castling[0] = true;
        }
        if (i == 'Q') {
            castling[1] = true;
        }
        if (i == 'k') {
            castling[2] = true;
        }
        if (i == 'q') {
            castling[3] = true;
        }
    }

    if (FenParts[3] == "-") {
        en_passant = -1;
    }
    else {
        en_passant = algToPos(FenParts[3]);
    }

    half_clock = std::stoi(FenParts[4]);
    full_clock = std::stoi(FenParts[4]);
}

std::string Board::export_FEN() {
    std::string FEN = "";
    for (int row = 0; row < 8; row++) {
        int space_count = 0;
        for (int col = 0; col < 8; col++) {
            if (letterbox[row*8 + col] == 0) {
                space_count += 1;
            }
            else {
                if (space_count > 0) {
                    FEN += std::to_string(space_count);
                    space_count = 0;
                }
                FEN += pointToChar[letterbox[row*8 + col]];
            }
        }
        if (space_count != 0) {
            FEN += std::to_string(space_count);
        }

        if (row < 7) {
            FEN += "/";
        }
    }

    return FEN;
}


std::string posToAlg(int pos)   { // 0 is top left, 63 is bottom right
    std::string colString = "abcdefgh";
    std::string rowString = "12345678";
    return std::string(1,colString[pos%8]) + rowString[7 - pos/8];
}

void Board::make_move(Move * move) {
    int moving_piece_value = this->letterbox[move->startPos];
    int taken_piece_value = this->letterbox[move->endPos];
    int moving_piece_idx = m[pointToChar[moving_piece_value]];
    int taken_piece_idx = m[pointToChar[taken_piece_value]];

    if (move->isEnPassant) {
        if (white) {
            // remove black pawn
            this->letterbox[move->endPos+8] = 0;
            this->bitboards[p] &= ~(canchor >> (move->endPos+8));
            this->bitboards[black]  &= ~(canchor >> (move->endPos+8));


            this->letterbox[move->startPos] = 0;
            this->bitboards[white] &= ~(canchor >> (move->startPos));
            this->bitboards[P] &= ~(canchor >> (move->startPos));

            this->letterbox[move->endPos] = charToPoint[reverse_m[p]];
            this->bitboards[white] |= canchor >> move->endPos;
            this->bitboards[P] |= canchor >> move->endPos; // add back
        }
        else {
            // remove white  pawn
            this->letterbox[move->endPos-8] = 0;
            this->bitboards[P] &= ~(canchor >> (move->endPos-8));
            this->bitboards[white]  &= ~(canchor >> (move->endPos-8));

            this->letterbox[move->startPos] = 0;
            this->bitboards[black] &= ~(canchor >> (move->startPos));
            this->bitboards[p] &= ~(canchor >> (move->startPos));

            this->letterbox[move->endPos] = charToPoint[reverse_m[P]];
            this->bitboards[black] |= canchor >> move->endPos;
            this->bitboards[p] |= canchor >> move->endPos; // add back

        }
    }
    else {


        letterbox[move->startPos] = 0;
        this->bitboards[moving_piece_idx] &= ~(canchor >> move->startPos); //remove piece from it's bitboard
        this->bitboards[moving_piece_idx/7 * 7] &= ~(canchor >> move->startPos); // remove piece from its color bitboard

        letterbox[move->endPos] = charToPoint[reverse_m[moving_piece_idx]];
        this->bitboards[moving_piece_idx] |= canchor >> move->endPos; // add back
        this->bitboards[moving_piece_idx/7 * 7] |= canchor >> move->endPos;
        if (taken_piece_value != 0) {
            this->bitboards[taken_piece_idx] &= ~(canchor >> move->endPos);
            this->bitboards[(taken_piece_idx/7) * 7] &= ~(canchor >> move->endPos); // correct this
        }
    }
    // check if we are putting something in enpassantable position
    en_passant = -1;
    if (moving_piece_idx == p || moving_piece_idx == P) {
        if (abs(move->startPos - move->endPos) == 16) {
            en_passant = move->endPos;
        }
    }

    game_moves.push_back(*move);
    this->white = !white;
    this->full_clock++;
}

std::vector<Move> Board::set_legal_moves() {
    //this->legal_moves = get_legal_moves(this);



}

void Board::undo_move() {
    Move move = game_moves.back();
    game_moves.pop_back();
    // if (white) {
    //     std::cout << "black" << std::endl;
    //     print_letterbox(letterbox);
    // }
    int moved_piece_value = this->letterbox[move.endPos];
    // if (moved_piece_value == move.movedPiece) {
    //     std::cout << "something went wrong" << std::endl;
    // }
    int taken_piece_value = move.pieceTaken;
    int moved_piece_idx = move.movedPiece;
    int taken_piece_idx = m[pointToChar[taken_piece_value]];

    if (move.isEnPassant) {
        if (white) { // previous turn was blacck
            // remove black pawn
            this->letterbox[move.endPos+8] = charToPoint[reverse_m[P]];
            this->bitboards[p] |= (canchor >> (move.endPos+8));
            this->bitboards[black]  |= (canchor >> (move.endPos+8));


            this->letterbox[move.startPos] = charToPoint[reverse_m[p]];
            this->bitboards[white] |= (canchor >> (move.startPos));
            this->bitboards[P] |= (canchor >> (move.startPos));

            this->letterbox[move.endPos] = 0;
            this->bitboards[white] &= ~(canchor >> move.endPos);
            this->bitboards[P] &= ~(canchor >> move.endPos); // add back
        }
        else {
            // remove black pawn
            this->letterbox[move.endPos-8] = charToPoint[reverse_m[p]];
            this->bitboards[P] |= (canchor >> (move.endPos-8));
            this->bitboards[white]  |= (canchor >> (move.endPos+8));


            this->letterbox[move.startPos] = charToPoint[reverse_m[P]];
            this->bitboards[black] |= (canchor >> (move.startPos));
            this->bitboards[p] |= (canchor >> (move.startPos));

            this->letterbox[move.endPos] = 0;
            this->bitboards[black] &= ~(canchor >> move.endPos);
            this->bitboards[p] &= ~(canchor >> move.endPos); // add back
        }
    }
    else {
        this->bitboards[moved_piece_idx] &= ~(canchor >> move.endPos); //remove piece from it's bitboard
        this->bitboards[moved_piece_idx/7 * 7] &= ~(canchor >> move.endPos); // remove piece from its color bitboard

        this->letterbox[move.startPos] = charToPoint[reverse_m[moved_piece_idx]];
        this->bitboards[moved_piece_idx] |= canchor >> move.startPos; // add back
        this->bitboards[moved_piece_idx/7 * 7] |= canchor >> move.startPos;

        this->letterbox[move.endPos] = charToPoint[reverse_m[taken_piece_idx]];
        if (taken_piece_value != 0) {
            this->bitboards[taken_piece_idx] |= (canchor >> move.endPos);
            this->bitboards[(taken_piece_idx/7) * 7] |= (canchor >> move.endPos); // correct this
        }
    }
    // check if we are putting something in enpassantable position
    en_passant = -1;
    if (move.isEnPassant) {
        if (white) { // prev turn was white, so process black
            en_passant = move.endPos+8;
        }
        else {
            en_passant = move.endPos-8;
        }
    }

    this->white = !white;
    this->full_clock--;
}

