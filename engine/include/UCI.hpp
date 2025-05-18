//
// Created by cinna on 17/05/25.
//

#ifndef UCI_HPP
#define UCI_HPP

#include <string>
#include <iostream>
#include "../include/Moves.hpp"
#include "../include/Global.hpp"
#include "../include/Board.hpp"
#include "../include/Single_node_evaluation.hpp"
#include "../include/minimax.h"

void uci_loop();
void parse_uci_command(const std::string& command);

// commands
void uci();
void isReady();
void setOption(const std::string& args);
void newGame();
void position(const std::string& args);
void go(const std::string& args);
void stop();
void quit();

// debugging, utility, life (the shit bits)
void id();          // hello chat Im cappuccino made by two idiots
void ok();          // we are happy :)

#endif //UCI_HPP
