#pragma once

#include "Board.hpp"
#include "PuzzleNode_stars.hpp"
#include "includes.hpp"

class Backtracking
{
public:
    Backtracking(std::shared_ptr<Board> initial);
    ~Backtracking();

    bool solver();

private:
    std::shared_ptr<Board> _initial_board;

    std::stack<std::shared_ptr<PuzzleNode_stars>> _solution_stack;
    std::unordered_set<std::string>               _visited_nodes;

    bool is_visited(std::string b);

    void do_backtrack(std::shared_ptr<PuzzleNode_stars> current_node);

    float start;

    float end;

    size_t iterations;
};