//
// Created by elmo on 07/08/24.
//

#include "Headers/Global.hpp"
#include "Headers/Moves.hpp"

#include <random>
#include <vector>

#include "Headers/Board.hpp"

std::array<std::map<int, ULL>, 64> lookupTable;

std::list<move> get_legal_moves(Board board){

    std::list<move> whiteMoves;
    std::list<move> blackMoves;

    // make sure the lookup table is assigned
    // (dont worry map.empty() is O(1) so this is fine for repeated use)
    if (lookupTable[0].empty())
    {
        lookupTable = load_lookup_tables();
    }
    //index of specific bitboards: 0 = black; 1 = p; 2 = r; 3 = n; 4 = b; 5 = q; 6 = k; 7 = white; 8 = p; 9 = r; 10 = n; 11 = b; 12 = q; 13 = k;
    std::array<ULL,64> pseduo_legal_moves = std::array<ULL,64>();
    std::array<ULL,64> takes_legal_moves= std::array<ULL,64>();
    for(int i = 0; i <= 63; i++)
    {
        int pieceType = pointToIdx[board.letterbox[i]];
        //
        pseduo_legal_moves[i] = lookupTable[pieceType][i];
        ULL takes, occupied;
        if(pieceType < white)
        {
            takes = pseduo_legal_moves[i] & board.bitboards[white];
        }
        else{
            takes = pseduo_legal_moves[i] & board.bitboards[black];
        }
        occupied = pseduo_legal_moves[i] & (board.bitboards[white] | board.bitboards[black]);
        takes_legal_moves[i] =0;

    }



    // STILL NEEDS TO BE IMPLEMENTED
    return whiteMoves;
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

        // Start with pawns Black
        ULL possibleMoves = 0;

        if(distanceTop >= 2) possibleMoves += (1ul << (i + 16));
        if(distanceTop >= 1) possibleMoves += (1ul << (i + 8));
        if(distanceTop >= 1 && distanceLeft >= 1) possibleMoves += (1ul << (i + 9));
        if(distanceTop >= 1 && distanceRight >= 1) possibleMoves += (1ul << (i + 7));

        lookupTable[63 - i].insert({p, possibleMoves});

        // Proceed with White pawns

        possibleMoves = 0;

        if(distanceBot >= 2) possibleMoves += (1ul << (i - 16));
        if(distanceBot >= 1) possibleMoves += (1ul << (i - 8));
        if(distanceBot >= 1 && distanceLeft >= 1) possibleMoves += (1ul << (i - 9));
        if(distanceBot >= 1 && distanceRight >= 1) possibleMoves += (1ul << (i - 7));

        lookupTable[63 - i].insert({P, possibleMoves});

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
        lookupTable[63-i].insert({r, possibleMoves});

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
        lookupTable[63-i].insert({b, possibleMoves});

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
        lookupTable[63-i].insert({n, possibleMoves});

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
        lookupTable[63-i].insert({q, possibleMoves});

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
        lookupTable[63-i].insert({k, possibleMoves});
    }

//adding blank spaces
    for(int i = 0; i < 64; i++)
    {
        lookupTable[i].insert({0, 0});
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

ULL find_rook_legal_moves(int position, ULL blockers) {
    ULL legal_moves = 0;

    // check left starting from position
    int cur_position = position;
    int row = cur_position / 8;
    int col = cur_position % 8;

    cur_position = position - 1;
    while (cur_position%8 != 7) {
        if (blockers & (1ul << cur_position) != 0)
            break;

        legal_moves |= (1ul << cur_position);
        cur_position -= 1;

    }

    // check right starting from position
    cur_position = position + 1;
    while (cur_position%8 != 0) {
        if (blockers & (1ul << cur_position) != 0)
            break;

        legal_moves |= (1ul << cur_position);
        cur_position += 1;
    }

    // moving up
    cur_position = position - 8;
    while (cur_position > 0) {
        if (blockers & (1ul << cur_position) != 0)
            break;
        legal_moves |= (1ul << cur_position);
        cur_position -= 8;
    }
    // moving down
    cur_position = position + 8;
    while (cur_position < 64) {
        if (blockers & (1ul << cur_position) != 0)
            break;
        legal_moves |= (1ul << cur_position);
        cur_position += 8;
    }
    return legal_moves;
}
/// @brief
/// Given a movement map, return all possible blocker positions
/// @return
/// map with all possible blocker positions
std::map<ULL, ULL> generate_blocker_map(int position, ULL movement_map, ULL (*find_legal_moves)(int,ULL) ) {
    std::vector<ULL> movement_indices;
    std::map<ULL,ULL> blocker_to_legal_moves = std::map<ULL, ULL>();
    for (int i = 0; i < 64; i++) {
        ULL t = movement_map & (1ull << i) ;
        if ((movement_map & (1ull << i)) != 0){
            movement_indices.push_back(i);
        }
    }
    //calculating size of the map
    ULL number_of_possibilities = static_cast<unsigned long long>(std::pow(2, movement_indices.size()));

    for (int i = 0; i < number_of_possibilities; i++) {
        ULL blocker_map = 0;
        for (int j = 0; j < movement_indices.size(); j++) {
            if ((movement_map & (1ull << j)) != 0) {
                blocker_map |= (1ull << movement_indices[j]);
            }
            // print_bit_board(blocker_map);
            blocker_to_legal_moves.insert({blocker_map,find_legal_moves(position, blocker_map)});
            // print_bit_board(blocker_to_legal_moves[blocker_map]);
        }
    }
    return blocker_to_legal_moves;
}




/// @brief 
/// UNIMPLEMENTED
/// @return 
/// Wether the lookup table that is saved is valid
bool validate_lookup_table(){

    return true;
}
