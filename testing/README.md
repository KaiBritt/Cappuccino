# Testing move generation:
## FEN strings (all test strings in form of white legal moves):
### Empty board piece moving
- King centre: 8/8/8/8/3K4/8/8/8 w - - 0 1 (8 legal moves)
- King edge: 8/8/8/8/8/8/8/K7 w - - 0 1 (3 legal moves)
- Queen Centre: 8/8/8/8/4Q3/8/8/8 w - - 0 1 (27 legal moves)
- Queen edge: 8/8/8/8/8/8/8/Q7 w - - 0 1 (14 legal moves)
- Rook: 8/8/8/3R4/8/8/8/8 w - - 0 1 (14 legal moves)
- Bishop centre: 8/8/8/3B4/8/8/8/8 w - - 0 1 (13 legal moves)
- Bishop edge: 8/8/8/8/8/8/8/B7 w - - 0 1 (7 legal moves)
- Knight centre: 8/8/8/3N4/8/8/8/8 w - - 0 1 (8 legal moves)
- Knight edge: 8/8/8/1N6/8/8/8/8 w - - 0 1 (6 legal moves)
- Pawn double move: 8/8/8/8/8/8/3P4/8 w - - 0 1 (2 legal moves)
- Pawn single move: 8/8/8/8/8/4P3/8/8 w - - 0 1 (1 legal moves)

### Blockers piece moving
- King takes: 8/8/8/8/4K3/3p1p2/8/8 w - - 0 1 (8 legal moves)
- Queen sliding/blockers: 8/4P3/8/2p1Q1P1/5p2/4p3/8/8 w - - 0 1 (24 legal moves)
- Bishop sliding/blockers 8/1p6/4p3/3B4/4P3/1p6/8/8 w - - 0 1 (6 legal moves)
- Rook sliding/blockers: 8/3p4/p2R1p2/8/8/3P4/8/8 w - - 0 1 (9 legal moves)
- Pawn takes: 8/8/8/3n1n2/4P3/8/8/8 w - - 0 1 (3 legal moves)

### King stalemate
- Stalemate by rooks: 1r6/8/8/8/8/8/7r/K7 w - - 0 1
- Stalemate by queen: 1q6/8/8/8/8/8/7q/K7 w - - 0 1
- Stalemate by bishops: 6b1/7b/8/8/8/8/8/K1b5 w - - 0 1
- Stalemate by knights: 8/8/8/8/1n6/3n4/3n4/K7 w - - 0 1
- Stalemate by pawns: 8/8/8/8/8/1pp5/2p5/K7 w - - 0 1

### King checked
- Checked by rooks: r7/8/8/8/8/8/7r/K7 w - - 0 1 (1 legal move)
- Checked by queens: 8/8/8/4q3/8/8/7q/K7 w - - 0 1 (1 legal move)
- Checked by bishops: 8/8/8/8/2bb4/8/8/K7 w - - 0 1 (1 legal move)
- Checked by knights: 8/8/8/8/8/1nn5/8/K7 w - - 0 1 (1 legal move)
- Checked by pawns: 8/8/8/8/8/pp6/1p6/K7 w - - 0 1 (1 legal move)

### King checkmate
- Queen checkmate: 8/8/8/8/8/2q5/1q6/K7 w - - 0 1
- Ladder checkmate: 1r6/r7/8/8/8/8/8/K7 w - - 0 1
- Rook, Knight checkmate: 8/8/8/8/8/1nn5/7r/K7 w - - 0 1
- Bishop checkmate: 8/8/8/8/2b5/2b5/2b5/K7 w - - 0 1


## Run move generation tests
- Lmao you wish this existed
