#pragma once

#include "Board.hpp"
#include "PuzzleNode_stars.hpp"
#include "includes.hpp"

class GreedyFirst
{
public:
    GreedyFirst(Board *initial);

    ~GreedyFirst()
    {
        delete this->_initial_node;
    };

    bool solver();

private:
    PuzzleNode_stars *_initial_node;

    std::vector<PuzzleNode_stars *> successors(PuzzleNode_stars *node);

    std::priority_queue<PuzzleNode_stars *, std::vector<PuzzleNode_stars *>, PuzzleNode_stars_comparator_gf> _open_set;

    std::unordered_set<std::string> _cosed_set;

    float start;

    float end;
};