#pragma once

#include "Board.hpp"
#include "PuzzleNode_stars.hpp"
#include "includes.hpp"

class BFS
{
public:
    BFS(std::shared_ptr<Board> initial);

    bool solver();

private:
    std::shared_ptr<Board> _initial_board;

    std::vector<std::shared_ptr<PuzzleNode_stars>> successors(std::shared_ptr<PuzzleNode_stars> node);

    std::queue<std::shared_ptr<PuzzleNode_stars>> _frontier;

    std::unordered_set<std::string> _explored;

    float start;

    float end;
};