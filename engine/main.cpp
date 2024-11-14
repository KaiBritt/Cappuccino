#include <iostream>
#include "Headers/Moves.hpp"
#include "Headers/Global.hpp"
#include "Headers/Board.hpp"

int main()
{
    std::array<std::unordered_map<int, ULL>, 64> tables = generate_lookup_table();
    // store_lookup_tables(tables);
    // std::array<std::map<int, ULL>, 64> tables  = load_lookup_tables();
    std::cout << std::endl;
    // generate_blocker_map(0,tables[0][PieceType::r],find_rook_legal_moves);
    // std::array<std::unordered_map<int, std::unordered_map<unsigned long long, unsigned long long>>, 64> blockers = generate_blocker_table(tables);
    // store_blocker_table(blockers);
    Board test_board = Board("8/4p3/8/2P1q1p1/5P2/4P3/8/8");
    std::cout << test_board.export_FEN() << std::endl;
    // print_letterbox(test_board.letterbox);
    get_legal_moves( &test_board);
    std::cout << "finished "  <<std::endl;
    return 0;
}
