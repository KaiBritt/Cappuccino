//
// Created by cinna on 17/05/25.
//

#include "../include/UCI.hpp"
#include "../include/Board.hpp"

#define end std::endl


void id() {
    // you already know who I am :pray:
    std::cout << "id name Cappuccino" << end;
    std::cout << "id author Mosh & Cinna" << end;
}


void ok() {
    // send options that you can change (or maybe you cant actually change it kekw)
    // format: option name {thing} type {thing} default {thing} min {thing} max {thing}
    // std::cout << "option name Hash type spin default 16 min 1 max 128" << end;
    std::cout << "option name Depth type spin default 11 min 1 max 32" << end;

    // after all that cringe say that we are vibing
    std::cout << "uciok" << end;
}


void parse_uci_command(const std::string &command, Board& board) {
    // do magic to split the command by spaces
    std::istringstream iss(command);
    std::vector<std::string> tokens;
    std::string token;
    while (iss >> token) {
        tokens.push_back(token);
    }

    if (tokens[0] == "uci")
        uci();
    else if (tokens[0] == "isready")
        isReady();
    else if (tokens[0] == "ucinewgame")
        newGame(board);
    else if (tokens[0] == "position")
        position(tokens, board);
    else if (tokens[0] == "setoption")
        setOption(tokens);
    else if (tokens[0] == "go")
        go(tokens);
    else if (tokens[0] == "quit")
        quit();
}


void uci() {
    // say hi etc etc blah blah blah
    id();
    ok();
}


void isReady() {
    std::cout << "readyok" << end;
}


void setOption(const std::vector<std::string>& args) {
    return;
}


void newGame(Board& board) {
    // initialise our board as a brand new game
    board = Board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

    std::cout << "isready" << end; // always gotta say we are ready
}


void position(const std::vector<std::string> args, Board& board) {
    // find the latest move
    std::string lastMove = args.back();

    // turn the latest move into an actual move
    //TODO:

    // make the move
    // board.make_move()

    return;
}


void go(const std::vector<std::string>& args) {
    return;
}


void stop() {
    return;
}


void quit() {
    exit(0);
}


void uci_loop() {
    // initialise the board (just the starting pos board thingy)
    Board board = Board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

    // initialise the line string thing command variable for later
    std::string line;

    // while there are still lines (commands) to read keep doing it. such is life
    while (std::getline(std::cin, line)) {
        if (line.empty()) continue; // ignore empty lines because they are empty...
        parse_uci_command(line, board);
    }
}
