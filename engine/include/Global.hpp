#ifndef GLOBAL_HPP

#define ULL unsigned long long
#pragma once
#define PAWN 100
#define KNIGHT 300
#define BISHOP 320
#define ROOK 500
#define QUEEN 900
#define KING 20000
#define canchor 1ULL << 63

#include <iostream>
#include <list>
#include <map>
#include <array>

enum PieceType{
    black, p, r,n, b, q, k, white, P, R, N, B, Q, K
};

inline std::map<char,int> charToPoint{{'D',0},{'p',-100},{'r',-500},{'n',-300},{'b',-320},{'q',-900},{'k',-20000},{'W',0},{'P',100},{'R',500},{'N',300},{'B',320},{'Q',900},{'K',20000}};
inline std::map<int, PieceType> pointToPiece{{0,black },{-100, p},{-500, r},{-300, n},{-320, b},{-900, q},   {-20000, k},{100, P},{500, R},{300, N},{320, B},{900, Q},{20000,K}};
inline std::map<int, char> pointToChar{
     {0, 'W'},    {-100, 'p'},   {-500, 'r'},   {-300, 'n'},
     {-320, 'b'}, {-900, 'q'},   {-20000, 'k'}, {100, 'P'},
     {500, 'R'},  {300, 'N'},    {320, 'B'},    {900, 'Q'},
     {20000, 'K'}
};
#endif