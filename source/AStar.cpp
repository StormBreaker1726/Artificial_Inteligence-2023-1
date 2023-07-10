#include "AStar.hpp"
AStar::AStar(Board *b)
{
    this->_board = b;

#ifdef DEBUG
    std::cout << "Geting in to solver..." << std::endl;
#endif

    this->start = omp_get_wtime();
    bool result = this->solver();
    this->end   = omp_get_wtime();

#ifdef DEBUG
    std::cout << "Out of solver" << std::endl;
#endif

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

AStar::~AStar()
{
    while (!this->_open_set.empty())
    {
        PuzzleNode_stars *temp = this->_open_set.top();
        this->_open_set.pop();
        delete temp;
    }
}

bool AStar::solver()
{
    _solution_cost        = 0;
    _total_expanded_nodes = 0;
    _total_visited_nodes  = 0;

    PuzzleNode_stars *_start_node = new PuzzleNode_stars(this->_board);
    _start_node->depth            = 0;

    _start_node->h = this->_board->h1();
    _start_node->f = _start_node->h;

    this->_open_set.push(_start_node);

    while (!this->_open_set.empty() && (omp_get_wtime() - this->start) < 120)
    {
        PuzzleNode_stars *_current_node = this->_open_set.top();
        this->_open_set.pop();

        this->_total_visited_nodes++;

        if (_current_node->_state->goal_state_reached())
        {
            std::cout << "Objective reached!" << std::endl;
            std::cout << "Moves:" << std::endl;
            _current_node->_state->print_moves_map();
            std::cout << "Path size = " << _current_node->_state->size_path() << std::endl;
            std::cout << "Solution cost = " << _current_node->g << std::endl;
            std::cout << "Expanded nodes = " << _total_expanded_nodes << std::endl;
            std::cout << "Visited nodes = " << _total_visited_nodes << std::endl;
            std::cout << "Depth: " << _current_node->depth << std::endl;
            _average_branching_factor = static_cast<float>(_total_expanded_nodes - 1) / static_cast<float>(_total_visited_nodes);
            std::cout << "Average branching factor = " << _average_branching_factor << std::endl;
            // _current_node->_state->print();
            return true;
        }

        this->_closed_set[_current_node->_state] = _current_node;
        this->_total_expanded_nodes++;

        std::vector<PuzzleNode_stars *> _successors = this->sucessors(_current_node);

        for (PuzzleNode_stars *sucessor : _successors)
        {
            if (this->_open_set_contains(sucessor->_state) || this->_closed_set_contains(sucessor->_state))
            {
                delete sucessor->_state;
                delete sucessor;
                continue;
            }

            sucessor->g     = _current_node->g + 1;
            sucessor->h     = sucessor->_state->calculate_h1();
            sucessor->f     = sucessor->g + sucessor->h;
            sucessor->depth = _current_node->depth + 1;

            this->_open_set.push(sucessor);
        }

        delete _current_node;
    }

    return false;
}

std::vector<PuzzleNode_stars *> AStar::sucessors(PuzzleNode_stars *node)
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
        _successors.push_back(success_node);
    }

    if (empy_row < rank - 1)
    {
        Board *success_board = new Board(_current_state);

        success_board->move_down();

        PuzzleNode_stars *success_node = new PuzzleNode_stars(success_board, node, "Down");
        _successors.push_back(success_node);
    }

    if (empy_column < rank - 1)
    {
        Board *success_board = new Board(_current_state);
        success_board->move_right();

        PuzzleNode_stars *success_node = new PuzzleNode_stars(success_board, node, "Right");
        _successors.push_back(success_node);
    }

    if (empy_column > 0)
    {
        Board *success_board = new Board(_current_state);

        success_board->move_left();

        PuzzleNode_stars *success_node = new PuzzleNode_stars(success_board, node, "Left");
        _successors.push_back(success_node);
    }

    return _successors;
}