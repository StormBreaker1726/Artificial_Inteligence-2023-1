#pragma once

#include "Board.hpp"
#include "PuzzleNode_stars.hpp"
#include "includes.hpp"

class DFS
{
public:
    DFS(std::shared_ptr<Board> initial);

    bool solver();

private:
    std::shared_ptr<Board> _initial_board;

    std::vector<std::shared_ptr<PuzzleNode_stars>> successors(std::shared_ptr<PuzzleNode_stars> node);

    std::stack<std::shared_ptr<PuzzleNode_stars>> _solution_stack;

    std::unordered_set<std::string> _visited;

    float start;

    float end;

    size_t iterations;
};