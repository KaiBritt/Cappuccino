#include <gtest/gtest.h>
#include "../engine/include/Board.h"

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


TEST(Move_Generation, Basic_Move_Gen ) {

    for (int i = 0; i < tests.size();i++){
        Board board = Board(tests[i][0]);
        auto legal_moves = board.get_legal_moves();
        EXPECT_EQ(legal_moves.first.size() + legal_moves.second.size(), std::stoi(tests[i][1]));
   }
}
