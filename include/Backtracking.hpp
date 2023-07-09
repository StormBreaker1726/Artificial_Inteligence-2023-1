#pragma once

#include "Board.hpp"
#include "PuzzleNode_stars.hpp"
#include "includes.hpp"

class Backtracking
{
public:
    Backtracking(Board *initial);
    ~Backtracking();

    bool solver();

private:
    Board *_initial_board;

    std::stack<PuzzleNode_stars *>  _solution_stack;
    std::unordered_set<std::string> _visited_nodes;

    bool is_visited(std::string b);

    void do_backtrack(PuzzleNode_stars *current_node);

    float start;

    float end;
};