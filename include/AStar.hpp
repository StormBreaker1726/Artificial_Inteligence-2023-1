#pragma once

#include "PuzzleNode_stars.hpp"
#include "includes.hpp"

class AStar
{
public:
    AStar(std::shared_ptr<Board> b);
    ~AStar()
    {
    }

    bool solver();

    bool _open_set_contains(std::shared_ptr<Board> board)
    {
        std::priority_queue<std::shared_ptr<PuzzleNode_stars>, std::vector<std::shared_ptr<PuzzleNode_stars>>, PuzzleNode_stars_comparator> tempQueue =
            this->_open_set;

        while (!tempQueue.empty())
        {
            std::shared_ptr<PuzzleNode_stars> node = tempQueue.top();
            tempQueue.pop();

            if (node->_state->equals(board))
            {
                return true;
            }
        }

        return false;
    }

    bool _closed_set_contains(std::shared_ptr<Board> state)
    {
        return this->_closed_set.find(state) != this->_closed_set.end();
    }

    float branching_factor;

    unsigned int cost;

    unsigned int visited_nodes;

    unsigned int expanded_nodes;

    size_t max_depth;

    std::vector<size_t> nodes_per_depth;

private:
    std::priority_queue<std::shared_ptr<PuzzleNode_stars>, std::vector<std::shared_ptr<PuzzleNode_stars>>, PuzzleNode_stars_comparator> _open_set;

    std::unordered_map<std::shared_ptr<Board>, std::shared_ptr<PuzzleNode_stars>> _closed_set;

    float start;

    float end;

    std::shared_ptr<Board> _board;

    std::vector<std::shared_ptr<PuzzleNode_stars>> sucessors(std::shared_ptr<PuzzleNode_stars> node);

    float calculate_branching_factor(std::shared_ptr<PuzzleNode_stars>& root);
};