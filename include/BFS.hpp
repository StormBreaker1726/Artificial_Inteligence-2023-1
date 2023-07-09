#pragma once

#include "Board.hpp"
#include "PuzzleNode_stars.hpp"
#include "includes.hpp"

class BFS
{
public:
    BFS(Board *initial);

    bool solver();

private:
    Board *_initial_board;

    std::vector<PuzzleNode_stars *> successors(PuzzleNode_stars *node);

    std::queue<PuzzleNode_stars *> _frontier;

    std::unordered_set<std::string> _explored;

    float start;

    float end;
};