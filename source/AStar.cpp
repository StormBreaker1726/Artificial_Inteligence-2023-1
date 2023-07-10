#include "AStar.hpp"
AStar::AStar(std::shared_ptr<Board> b)
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

bool AStar::solver()
{
    // PuzzleNode_stars *_start_node = new PuzzleNode_stars(this->_board);
    std::shared_ptr<PuzzleNode_stars> _start_node = std::make_shared<PuzzleNode_stars>(this->_board);
    _start_node->depth                            = 0;

    _start_node->h = this->_board->h1();
    _start_node->f = _start_node->h;

    this->_open_set.push(_start_node);

    while (!this->_open_set.empty() && (omp_get_wtime() - this->start) < 120)
    {
        std::shared_ptr<PuzzleNode_stars> _current_node = this->_open_set.top();
        this->_open_set.pop();

        if (_current_node->_state->goal_state_reached())
        {
            std::cout << "Objective reached!" << std::endl;
            std::cout << "Moves:" << std::endl;
            _current_node->_state->print_moves_map();
            std::cout << "Depth: " << _current_node->depth << std::endl;
            _current_node->_state->print();
            return true;
        }

        this->_closed_set[_current_node->_state] = _current_node;

        std::vector<std::shared_ptr<PuzzleNode_stars>> _successors = this->sucessors(_current_node);

        for (std::shared_ptr<PuzzleNode_stars> sucessor : _successors)
        {
            if (this->_open_set_contains(sucessor->_state) || this->_closed_set_contains(sucessor->_state))
            {
                // delete sucessor;
                continue;
            }

            sucessor->g     = _current_node->g + 1;
            sucessor->h     = sucessor->_state->calculate_h1();
            sucessor->f     = sucessor->g + sucessor->h;
            sucessor->depth = _current_node->depth + 1;

            this->_open_set.push(sucessor);
        }
    }

    return false;
}

std::vector<std::shared_ptr<PuzzleNode_stars>> AStar::sucessors(std::shared_ptr<PuzzleNode_stars> node)
{
    std::vector<std::shared_ptr<PuzzleNode_stars>> _successors;

    std::shared_ptr<Board> _current_state = node->_state;

    size_t rank = _current_state->rank();

    size_t empy_row    = _current_state->empty_position().first;
    size_t empy_column = _current_state->empty_position().second;

    if (empy_row > 0)
    {
        std::shared_ptr<Board> success_board = std::make_shared<Board>(_current_state);
        success_board->move_up();

        std::shared_ptr<PuzzleNode_stars> success_node = std::make_shared<PuzzleNode_stars>(success_board, node, "Up");
        _successors.push_back(success_node);
    }

    if (empy_row < rank - 1)
    {
        std::shared_ptr<Board> success_board = std::make_shared<Board>(_current_state);

        success_board->move_down();

        std::shared_ptr<PuzzleNode_stars> success_node = std::make_shared<PuzzleNode_stars>(success_board, node, "Down");
        _successors.push_back(success_node);
    }

    if (empy_column < rank - 1)
    {
        std::shared_ptr<Board> success_board = std::make_shared<Board>(_current_state);
        success_board->move_right();

        std::shared_ptr<PuzzleNode_stars> success_node = std::make_shared<PuzzleNode_stars>(success_board, node, "Right");
        _successors.push_back(success_node);
    }

    if (empy_column > 0)
    {
        std::shared_ptr<Board> success_board = std::make_shared<Board>(_current_state);

        success_board->move_left();

        std::shared_ptr<PuzzleNode_stars> success_node = std::make_shared<PuzzleNode_stars>(success_board, node, "Left");
        _successors.push_back(success_node);
    }

    return _successors;
}