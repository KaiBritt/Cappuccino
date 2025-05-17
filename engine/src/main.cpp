#include <iostream>

// #include "voronoi.h"
#include "../include/Moves.hpp"
#include "../include/Global.hpp"
#include "../include/Board.hpp"
#include "../include/Single_node_evaluation.hpp"
#include "../include/minimax.h"
int main()
{
    LookupTableArray lookup_table = generate_lookup_table();
    BlockerTableArray blocker_table = generate_blocker_table(lookup_table);
    // store_lookup_tables(tables);
    // std::array<std::map<int, ULL>, 64> tables  = load_lookup_tables();
    std::cout << std::endl;
    // generate_blocker_map(0,tables[0][PieceType::r],find_rook_legal_moves);
    // std::array<std::unordered_map<int, std::unordered_map<unsigned long long, unsigned long long>>, 64> blockers = generate_blocker_table(tables);
    // store_blocker_table(blockers);
    Board test_board = Board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    std::cout << test_board.export_FEN() << std::endl;
    // print_letterbox(test_board.letterbox);
    auto legal_moves = get_legal_moves( &test_board);
    std::string player_move;
    // std::cin >> player_move;
    std::cout << "num white moves: " << legal_moves.size() << std::endl;
    // for (auto move : legal_moves) {
    //     if (parseMoveStr(player_move) == move) {
    //         print_letterbox(test_board.letterbox);
    //         test_board.make_move(&move);
    //         print_letterbox(test_board.letterbox);
    //
    //     }
    // }
    // test_board.undo_move();
    // print_letterbox(test_board.letterbox);
    std::cout << "start minimax" << std::endl;
    Move best_move = find_best_move(&test_board,4);
    std::cout << evaluate_node(test_board.letterbox)<< std::endl;
    print_letterbox(test_board.letterbox);
    std::cout << "finished "  <<std::endl;
    std::cout << posToAlg(best_move.startPos) << posToAlg(best_move.endPos) << std::endl;
    return 0;
}
