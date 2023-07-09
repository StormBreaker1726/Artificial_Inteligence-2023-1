#pragma once

#include "Board.hpp"
#include "PuzzleNode_stars.hpp"
#include "includes.hpp"

class DFS
{
public:
    DFS(Board *initial);

    bool solver();

private:
    Board *_initial_board;

    std::vector<PuzzleNode_stars *> successors(PuzzleNode_stars *node);

    std::stack<PuzzleNode_stars *> _solution_stack;

    std::unordered_set<std::string> _visited;

    float start;

    float end;
};