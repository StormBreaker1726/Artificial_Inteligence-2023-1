#pragma once

#include "Board.hpp"
#include "PuzzleNode_stars.hpp"
#include "includes.hpp"

class UniformCost
{
public:
    UniformCost(std::shared_ptr<Board> initial);

    ~UniformCost(){
        // delete this->_initial_node;
    };

    bool solver();

private:
    std::shared_ptr<PuzzleNode_stars> _initial_node;

    std::vector<std::shared_ptr<PuzzleNode_stars>> successors(std::shared_ptr<PuzzleNode_stars> node);

    std::priority_queue<std::shared_ptr<PuzzleNode_stars>, std::vector<std::shared_ptr<PuzzleNode_stars>>, PuzzleNode_stars_comparator_gf> _open_set;

    std::unordered_set<std::string> _cosed_set;

    float start;

    float end;

    unsigned int cost;

    unsigned int visited_nodes;

    size_t max_depth;

    unsigned int expanded_nodes;
};