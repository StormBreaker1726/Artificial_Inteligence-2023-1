#pragma once
#include "Board.hpp"
#include "PuzzleNode_stars.hpp"

class IDAStar
{
public:
    IDAStar(Board *b_initial);

    bool solver();

private:
    unsigned int expanded_nodes;

    unsigned int visited_nodes;

    unsigned int branching_sum;

    float start;

    float end;

    Board *_board;

    std::priority_queue<PuzzleNode_stars *, std::vector<PuzzleNode_stars *>, PuzzleNode_stars_comparator> _open_set;

    std::unordered_set<std::string> _closed_set;

    std::vector<Board *> sucessors(Board *b);
};