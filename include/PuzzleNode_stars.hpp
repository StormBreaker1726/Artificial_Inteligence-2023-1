#pragma once

#include "includes.hpp"
#include "Board.hpp"

struct PuzzleNode_stars
{
    Board *_state;
    PuzzleNode_stars *_parent;

    std::string _caused_move;

    unsigned int g;
    unsigned int h;
    unsigned int f;

    PuzzleNode_stars(Board *puzzle, PuzzleNode_stars *par, std::string mv = "")
    {
        this->_state = puzzle;
        this->_parent = par;
        this->_caused_move = mv;
        g = 0;
        h = 0;
        f = 0;
    }
};