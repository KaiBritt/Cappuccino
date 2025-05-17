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


void parse_uci_command(const std::string &command) {
    if (command == "uci")
        uci();
    else if (command == "isready")
        isReady();
    else if (command == "ucinewgame")
        newGame();
    else if (command == "position")
        position(command);
    else if (command == "setoption")
        setOption(command);
    else if (command == "go")
        go(command);
    else if (command == "quit")
        quit();
}


void uci();
void isReady();
void setOption(const std::string& args);
void newGame();
void position(const std::string& args);
void go(const std::string& args);
void stop();
void quit();

void uci_loop() {
    // say hi!!!! :)
    id();
    ok();

    // get the command we just got sent
    std::string line;

    // while there are still lines (commands) to read keep doing it. such is life
    while (std::getline(std::cin, line)) {
        if (line.empty()) continue; // ignore empty lines because they are empty...
        parse_uci_command(line);
    }
}
