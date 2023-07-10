#pragma once

#include "Board.hpp"
#include "PuzzleNode_stars.hpp"
#include "includes.hpp"

class Greedy
{
public:
    Greedy(Board *initial);

    ~Greedy();

    bool solver();

private:
    float start;

    float end;

    Board *_initial_board;

    std::priority_queue<PuzzleNode_stars *, std::vector<PuzzleNode_stars *>, PuzzleNode_comparator> _open_list;

    std::unordered_set<std::string> _explored_set;

    PuzzleNode_stars *create_child_node(Board *board, PuzzleNode_stars *parent, std::string move);

    bool is_explored(Board *b);

    void successors(PuzzleNode_stars *node);
};