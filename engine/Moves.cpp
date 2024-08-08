//
// Created by elmo on 07/08/24.
//

#include "Headers/Global.hpp"
#include "Headers/Moves.hpp"

std::array<std::map<int, ULL>, 64> LookupTable;

/// @brief 
/// Gets legal moves for specific piece
// [STILL NEEDS TO BE IMPLEMENTED]
/// @param pieceIndex 
/// Index of the piece whos moves we want
/// @return 
/// Returns a bitboard for where this piece can move
ULL get_legal_moves(int pieceIndex){
    // make sure the lookup table is assigned
    // (dont worry map.empty() is O(1) so this is fine for repeated use)
    if (LookupTable[0].empty())
    {
        LookupTable = load_lookup_tables();
    }

    // STILL NEEDS TO BE IMPLEMENTED
    return LookupTable[0][p];
}

/// @brief 
/// If LookupTables.dat exists use load_lookup_tables instead
/// @return 
/// Returns array of maps with lookup tables
std::array<std::map<int, ULL>, 64> generate_lookup_table(){
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

/// @brief 
/// Stores tables lookups table into a LookupTables.dat file in binary format
/// @param tables 
/// the table we want to push into LookupTables.dat
void store_lookup_tables(std::array<std::map<int, ULL>, 64> tables){
    // Create a file to write into
    std::ofstream ofs("LookupTables.dat", std::ios::binary | std::ios::out);

        // Just to make sure
        if (!ofs) {
        std::cerr << "Error opening file for writing: LookupTables.dat" << std::endl;
        return;
    }

    // Convert everything into binary and write it out like a good boy
    for (const auto& mapElement : tables) {
        size_t mapSize = mapElement.size();
        ofs.write(reinterpret_cast<const char*>(&mapSize), sizeof(mapSize));

        for (const auto& pair : mapElement) {
            ofs.write(reinterpret_cast<const char*>(&pair.first), sizeof(pair.first));
            ofs.write(reinterpret_cast<const char*>(&pair.second), sizeof(pair.second));
        }
    }

    ofs.close();
}

/// @brief 
/// Loads the LookupTables.dat file
/// @return 
/// A std::array<std::map<int, ULL>, 64> in which you can do var[pieceIndex][PieceType] to geth the bitmap. For example: "myTable[42][p]"
std::array<std::map<int, ULL>, 64> load_lookup_tables() {
    std::array<std::map<int, ULL>, 64> tables;
    // We start a information stream where we read the tables in binary
    std::ifstream ifs("LookupTables.dat", std::ios::binary | std::ios::in);

    // Just a cheecky check to se if everything is as it should be
    if (!ifs) {
        std::cerr << "Error opening file for reading: LookupTables.dat" << std::endl;
        return tables;
    }

    // Read out the binary to form maps and put them in new elements
    for (auto& mapElement : tables) {
        size_t mapSize;
        ifs.read(reinterpret_cast<char*>(&mapSize), sizeof(mapSize));

        for (size_t i = 0; i < mapSize; ++i) {
            int key;
            ULL value;
            ifs.read(reinterpret_cast<char*>(&key), sizeof(key));
            ifs.read(reinterpret_cast<char*>(&value), sizeof(value));
            mapElement[key] = value;
        }
    }

    // No memory leaks here
    ifs.close();

    return tables;
}

/// @brief 
/// UNIMPLEMENTED
/// @return 
/// Wether the lookup table that is saved is valid
bool validate_lookup_table(){

    return true;
}

/// @brief 
/// Prints a bitboard into the terminal in a human readable format
/// @param bitboard 
/// The bitboard to print out
void print_bit_board(ULL bitboard) {
    // Idk, this is mosh code
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