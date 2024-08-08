//
// Created by elmo on 07/08/24.
//

#include "Headers/Global.hpp"
#include "Headers/Moves.hpp"

std::list<move> get_moves(std::map<int, ULL> pieceBitBoards){
    
    std::list<move> moveList = std::list<move>();

    return moveList;
}

std::array<std::map<int, ULL>, 64> GenerateLookupTable(){
    std::array<std::map<int, ULL>, 64> lookupTable;

    for(int i = 0; i < 64; i++)
    {

        int distanceLeft = 7 - i % 8;
        int distanceRight = i % 8;
        int distanceTop = 7 - i / 8;
        int distanceBot = i / 8;

        // Start with pawns
        ULL possibleMoves = 0;

        if(distanceTop >= 2) possibleMoves += (1ul << (i + 16));
        if(distanceTop >= 1) possibleMoves += (1ul << (i + 8));
        if(distanceTop >= 1 && distanceLeft >= 1) possibleMoves += (1ul << (i + 9));
        if(distanceTop >= 1 && distanceRight >= 1) possibleMoves += (1ul << (i + 7));

        lookupTable[63 - i].insert({p, possibleMoves});
        lookupTable[63 - i].insert({P, __builtin_bswap64(possibleMoves)});

    // then rooks
        possibleMoves = 0;
        for (int j = 1; j < 9; j++)
        {
            int column = i % 8;
            possibleMoves |= (1ul << (column + 8 * j));
            int row = i / 8;
            possibleMoves |= (1ul << (j - 1 + 8 * row));
        }

        possibleMoves &= ~(1ul << i);
        lookupTable[i].insert({r, possibleMoves});

    // then bishop
        possibleMoves = 0;
    
        for (int j = 1; j <= std::min(distanceLeft, distanceTop); j++)
        {
            possibleMoves |= (1ul << (i + 9 * j));
        }
        for (int j = 1; j <= std::min(distanceLeft, distanceBot); j++)
        {
        possibleMoves |= (1ul << (i + -7 * j));
        }
        for (int j = 1; j <= std::min(distanceBot, distanceRight); j++)
        {
            possibleMoves |= (1ul << (i + -9 * j));
        }
        for (int j = 1; j <= std::min(distanceTop, distanceRight); j++)
        {
            possibleMoves |= (1ul << (i + 7 * j));
        }

        possibleMoves &= ~(1ul << i);
        lookupTable[i].insert({b, possibleMoves});

    // then knight
        possibleMoves = 0;

        int indexes[8] = {17, 15, 10, -6, -10, 6, -17, -15};

        if(distanceTop >= 2 && distanceLeft >= 1) possibleMoves |= (1ul << i + 17);
        if(distanceTop >= 2 && distanceRight >= 1) possibleMoves |= (1ul << i + 15);
        if(distanceTop >= 1 && distanceLeft >= 2) possibleMoves |= (1ul << i + 10);
        if(distanceTop >= 1 && distanceRight >= 2) possibleMoves |= (1ul << i + 6);
        if(distanceBot >= 1 && distanceLeft >= 2) possibleMoves |= (1ul << i + -6);
        if(distanceBot >= 2 && distanceLeft >= 1) possibleMoves |= (1ul << i + -15);
        if(distanceBot >= 2 && distanceRight >= 1) possibleMoves |= (1ul << i + -17);
        if(distanceBot >= 1 && distanceRight >= 2) possibleMoves |= (1ul << i + -10);

        possibleMoves &= ~(1ul << i);
        lookupTable[i].insert({n, possibleMoves});

    // then queen
        possibleMoves = 0;
        distanceLeft = 7 - i % 8;
        distanceRight = i % 8;
        distanceTop = 7 - i / 8;
        distanceBot = i / 8;

        for (int j = 1; j <= std::min(distanceLeft, distanceTop); j++)
        {
            possibleMoves |= (1ul << (i + 9 * j));
        }
        for (int j = 1; j <= std::min(distanceLeft, distanceBot); j++)
        {
            possibleMoves |= (1ul << (i + -7 * j));
        }
        for (int j = 1; j <= std::min(distanceBot, distanceRight); j++)
        {
            possibleMoves |= (1ul << (i + -9 * j));
        }
        for (int j = 1; j <= std::min(distanceTop, distanceRight); j++)
        {
            possibleMoves |= (1ul << (i + 7 * j));
        }

        for (int j = 1; j < 9; j++)
        {
            int column = i % 8;
            possibleMoves |= (1ul << (column + 8 * j));
            int row = i / 8;
            possibleMoves |= (1ul << (j - 1 + 8 * row));
        }

        possibleMoves &= ~(1ul << i);
        lookupTable[i].insert({q, possibleMoves});

    // then king
        possibleMoves = 0;

        if(distanceTop >= 1) possibleMoves |= (1ul << i + 8);
        if(distanceLeft >= 1) possibleMoves |= (1ul << i + 1);
        if(distanceBot >= 1) possibleMoves |= (1ul << i + -8);
        if(distanceRight >= 1) possibleMoves |= (1ul << i + -1);

        if(distanceTop >= 1 && distanceLeft >= 1) possibleMoves |= (1ul << i + 9);
        if(distanceTop >= 1 && distanceRight >= 1) possibleMoves |= (1ul << i + 7);
        if(distanceBot >= 1 && distanceLeft >= 1) possibleMoves |= (1ul << i + -7);
        if(distanceBot >= 1 && distanceRight >= 1) possibleMoves |= (1ul << i + -9);

        possibleMoves &= ~(1ul << i);
        lookupTable[i].insert({k, possibleMoves});
    }

    return lookupTable;
}

void print_bit_board(ULL bitboard) {
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            ULL two_to_63 = 9223372036854775808UL;
            if ((bitboard & (two_to_63 >> (row*8 + col))) != 0) {
                printf("1");
            }
            else {
                printf("0");
            }
        }
        printf("\n");
    }

    return;
}