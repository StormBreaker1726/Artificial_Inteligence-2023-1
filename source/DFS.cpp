#include "DFS.hpp"

DFS::DFS(std::shared_ptr<Board> initial)
{
    this->_initial_board = std::make_shared<Board>(initial);

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
        if (this->iterations == LIM)
            printf("Iteration limit!\n");
        printf("Time spent in the algorithm: %e seconds\n", (this->end - this->start));
    }
}

bool DFS::solver()
{
    std::shared_ptr<PuzzleNode_stars> initial_node = std::make_shared<PuzzleNode_stars>(this->_initial_board);
    initial_node->depth                            = 0;
    this->_solution_stack.push(initial_node);

    this->iterations = 0;

    while (!this->_solution_stack.empty() && iterations < LIM)
    {
        this->iterations++;
        std::shared_ptr<PuzzleNode_stars> current_node = this->_solution_stack.top();
        this->_solution_stack.pop();

        if (current_node->_state->goal_state_reached())
        {
            std::cout << "Objective reached!" << std::endl;
            std::cout << "Moves:" << std::endl;
            current_node->_state->print_moves_map();
            std::cout << "Depth: " << current_node->depth << std::endl;
            current_node->_state->print();
            return true;
        }

        this->_visited.insert(current_node->_state->to_string());

        std::vector<std::shared_ptr<PuzzleNode_stars>> _successors = this->successors(current_node);
        for (std::shared_ptr<PuzzleNode_stars> successor : _successors)
        {
            if (this->_visited.find(successor->_state->to_string()) == this->_visited.end())
            {
                this->_solution_stack.push(successor);
            }
        }
    }

    return false;
}

std::vector<std::shared_ptr<PuzzleNode_stars>> DFS::successors(std::shared_ptr<PuzzleNode_stars> node)
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
        success_node->depth                            = node->depth + 1;
        _successors.push_back(success_node);
    }

    if (empy_row < rank - 1)
    {
        std::shared_ptr<Board> success_board = std::make_shared<Board>(_current_state);

        success_board->move_down();

        std::shared_ptr<PuzzleNode_stars> success_node = std::make_shared<PuzzleNode_stars>(success_board, node, "Down");
        success_node->depth                            = node->depth + 1;
        _successors.push_back(success_node);
    }

    if (empy_column < rank - 1)
    {
        std::shared_ptr<Board> success_board = std::make_shared<Board>(_current_state);
        success_board->move_right();

        std::shared_ptr<PuzzleNode_stars> success_node = std::make_shared<PuzzleNode_stars>(success_board, node, "Right");
        success_node->depth                            = node->depth + 1;
        _successors.push_back(success_node);
    }

    if (empy_column > 0)
    {
        std::shared_ptr<Board> success_board = std::make_shared<Board>(_current_state);

        success_board->move_left();

        std::shared_ptr<PuzzleNode_stars> success_node = std::make_shared<PuzzleNode_stars>(success_board, node, "Left");
        success_node->depth                            = node->depth + 1;
        _successors.push_back(success_node);
    }

    return _successors;
}