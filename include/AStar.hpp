#pragma once

#include "PuzzleNode_stars.hpp"
#include "includes.hpp"

class AStar
{
public:
    AStar(Board *b);
    ~AStar();

    bool solver();

    bool _open_set_contains(Board *board)
    {
        std::priority_queue<PuzzleNode_stars *, std::vector<PuzzleNode_stars *>, PuzzleNode_stars_comparator> tempQueue = this->_open_set;

        while (!tempQueue.empty())
        {
            PuzzleNode_stars *node = tempQueue.top();
            tempQueue.pop();

            if (node->_state->equals(board))
            {
                return true;
            }
        }

        return false;
    }

    bool _closed_set_contains(Board *state)
    {
        return this->_closed_set.find(state) != this->_closed_set.end();
    }

private:
    std::priority_queue<PuzzleNode_stars *, std::vector<PuzzleNode_stars *>, PuzzleNode_stars_comparator> _open_set;

    std::unordered_map<Board *, PuzzleNode_stars *> _closed_set;

    float start;

    float end;

    Board *_board;

    std::vector<PuzzleNode_stars *> sucessors(PuzzleNode_stars *node);

    int   _solution_cost;             // Custo da solução
    int   _total_expanded_nodes;      // Número total de nós expandidos
    int   _total_visited_nodes;       // Número total de nós visitados
    float _average_branching_factor;  // Valor médio do fator de ramificação da árvore de busca
};