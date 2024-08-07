//
// Created by kai on 8/6/24.
//

#include "./Headers/Board.hpp"


void print_bit_board(unsigned long long bitboard) {
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            if ((bitboard & (9223372036854775808UL >> (row*8 + col))) != 0) {
                printf("1");
            }
            else {
                printf("0");
            }
        }
        printf("\n");
    }
}


Board::Board(char * FEN) {
    //making bitboards first
    for (unsigned long long & bitboard : bitboards) {
        bitboard = 0;
    }
    int row = 0;
    int col = 0;

    int FEN_size = 0;
    while (FEN[FEN_size] != '\0') {
        FEN_size++;
    }
    printf("%d\n", '8' - '0');
    for (int cc = 0; cc < FEN_size; cc++){

            if (FEN[cc] == '/') {
                row+=1;
                col = 0;
            }
            else if ((1 <= (FEN[cc] - '0')) and ((FEN[cc] -'0') <= 9)){
                col += (FEN[cc] - '0') - 1;
            }
            else {
                int offset = row * 8 + col;
                bitboards[m[FEN[cc]]] = bitboards[m[FEN[cc]]] | (1UL<<(63 - offset));
                col += 1;
            }
        }

    //making black and white bitboardss
    for (int i = 1; i < 7; i++) {
        bitboards[m['D']] |= bitboards[m['D'] + i];
        bitboards[m['W']] |= bitboards[m['W'] + i];
     }
    print_bit_board(bitboards[m['p']]);

    //making human readable board #from bb
    char charMap[15] = "DprnbqkWPRNBQK";
    std::map<char,int> charToPoint{{'D',0},{'p',-100},{'r',-500},{'n',-300},{'b',-320},{'q',-900},{'k',-20000},{'W',0},{'P',100},{'R',500},{'N',300},{'B',320},{'Q',900},{'K',20000}};
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
}

