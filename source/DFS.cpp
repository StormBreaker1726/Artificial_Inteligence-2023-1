#include "DFS.hpp"

DFS::DFS(Board *initial)
{
    this->_initial_board = new Board(initial);

    this->start = omp_get_wtime();
    bool result = this->solver();
    this->end   = omp_get_wtime();

    if (result)
    {
        printf("Time to reach objective: %e seconds\n", (this->end - this->start));
    }
    else
    {
        if ((this->end - this->start) > 120)
            printf("Failed by time\n");
        printf("Time spent in the algorithm: %e seconds\n", (this->end - this->start));
    }
}

bool DFS::solver()
{
    size_t            lim          = 10000;
    PuzzleNode_stars *initial_node = new PuzzleNode_stars(this->_initial_board);
    initial_node->depth            = 0;
    this->_solution_stack.push(initial_node);

    size_t i = 0;

    while (!this->_solution_stack.empty() && i < lim)
    {
        PuzzleNode_stars *current_node = this->_solution_stack.top();
        this->_solution_stack.pop();

        if (current_node->_state->goal_state_reached())
        {
            std::cout << "Objective reached!" << std::endl;
            std::cout << "Moves:" << std::endl;
            current_node->_state->print_moves_map();
            std::cout << "Size of path = " << current_node->_state->size_path() << std::endl;
            std::cout << "Cost = " << current_node->_state->size_path() << std::endl;
            std::cout << "Depth: " << current_node->depth << std::endl;
            // current_node->_state->print();
            return true;
        }

        this->_visited.insert(current_node->_state->to_string());

        std::vector<PuzzleNode_stars *> _successors = this->successors(current_node);
        for (PuzzleNode_stars *successor : _successors)
        {
            if (this->_visited.find(successor->_state->to_string()) == this->_visited.end())
            {
                this->_solution_stack.push(successor);
            }
        }
        i++;
    }

    return false;
}

std::vector<PuzzleNode_stars *> DFS::successors(PuzzleNode_stars *node)
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