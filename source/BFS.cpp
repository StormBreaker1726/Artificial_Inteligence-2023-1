#include "BFS.hpp"

BFS::BFS(Board *initial)
{
    this->_initial_board = new Board(initial);

    this->start = omp_get_wtime();
    bool result = this->solver();
    this->end   = omp_get_wtime();

    if (result)
    {
        printf("Time to reach objective: %e seconds\n", (end - start));
    }
    else
    {
        if ((end - start) > 120)
            printf("Failed by time\n");
        printf("Time spent in the algorithm: %e seconds\n", (end - start));
    }
}

bool BFS::solver()
{
    PuzzleNode_stars *initial_node = new PuzzleNode_stars(this->_initial_board);
    initial_node->depth            = 0;
    this->_frontier.push(initial_node);

    while (!this->_frontier.empty())
    {
        PuzzleNode_stars *current_node = this->_frontier.front();
        this->_frontier.pop();

        if (current_node->_state->goal_state_reached())
        {
            std::cout << "Objective reached!" << std::endl;
            std::cout << "Moves:" << std::endl;
            current_node->_state->print_moves_map();
            std::cout << "Depth: " << current_node->depth << std::endl;
            current_node->_state->print();
            return true;
        }

        this->_explored.insert(current_node->_state->to_string());

        std::vector<PuzzleNode_stars *> successors_vector = this->successors(current_node);

        for (PuzzleNode_stars *successor : successors_vector)
        {
            if (!this->_explored.count(successor->_state->to_string()))
            {
                this->_frontier.push(successor);
                this->_explored.insert(successor->_state->to_string());
            }
            else
            {
                delete successor;
            }
        }
    }

    return false;
}

std::vector<PuzzleNode_stars *> BFS::successors(PuzzleNode_stars *node)
{
    std::vector<PuzzleNode_stars *> _successors;

    Board *_current_state = node->_state;

    size_t rank = _current_state->rank();

    size_t empy_row    = _current_state->empty_position().first;
    size_t empy_column = _current_state->empty_position().second;

    if (empy_row > 0)
    {
        Board *success_board = new Board(_current_state);
        success_board->move_up();

        PuzzleNode_stars *success_node = new PuzzleNode_stars(success_board, node, "Up");
        success_node->depth            = node->depth + 1;
        _successors.push_back(success_node);
    }

    if (empy_row < rank - 1)
    {
        Board *success_board = new Board(_current_state);

        success_board->move_down();

        PuzzleNode_stars *success_node = new PuzzleNode_stars(success_board, node, "Down");
        success_node->depth            = node->depth + 1;
        _successors.push_back(success_node);
    }

    if (empy_column < rank - 1)
    {
        Board *success_board = new Board(_current_state);
        success_board->move_right();

        PuzzleNode_stars *success_node = new PuzzleNode_stars(success_board, node, "Right");
        success_node->depth            = node->depth + 1;
        _successors.push_back(success_node);
    }

    if (empy_column > 0)
    {
        Board *success_board = new Board(_current_state);

        success_board->move_left();

        PuzzleNode_stars *success_node = new PuzzleNode_stars(success_board, node, "Left");
        success_node->depth            = node->depth + 1;
        _successors.push_back(success_node);
    }

    return _successors;
}
