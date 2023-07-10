#pragma once

#include "Board.hpp"
#include "PuzzleNode_stars.hpp"
#include "includes.hpp"

class Greedy
{
public:
    Greedy(std::shared_ptr<Board> initial);

    ~Greedy();

    bool solver();

private:
    float start;

    float end;

    std::shared_ptr<Board> _initial_board;

    std::priority_queue<std::shared_ptr<PuzzleNode_stars>, std::vector<std::shared_ptr<PuzzleNode_stars>>, PuzzleNode_comparator> _open_list;

    std::unordered_set<std::string> _explored_set;

    std::shared_ptr<PuzzleNode_stars> create_child_node(std::shared_ptr<Board> board, std::shared_ptr<PuzzleNode_stars> parent, std::string move);

    bool is_explored(std::shared_ptr<Board> b);

    void successors(std::shared_ptr<PuzzleNode_stars> node);

    unsigned int cost;

    unsigned int visited_nodes;

    unsigned int expanded_nodes;
};