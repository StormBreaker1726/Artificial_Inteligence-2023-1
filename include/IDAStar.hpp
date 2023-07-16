#pragma once
#include "Board.hpp"
#include "PuzzleNode_stars.hpp"

class IDAStar
{
public:
    IDAStar(std::shared_ptr<Board> b_initial);

    bool solver();

private:
    float start;

    float end;

    std::shared_ptr<Board> _board;

    std::priority_queue<std::shared_ptr<PuzzleNode_stars>, std::vector<std::shared_ptr<PuzzleNode_stars>>, PuzzleNode_stars_comparator> _open_set;

    std::unordered_set<std::string> _closed_set;

    std::vector<std::shared_ptr<Board>> sucessors(std::shared_ptr<Board> b);

    unsigned int cost;

    unsigned int visited_nodes;

    unsigned int expanded_nodes;

    size_t max_depth;
};