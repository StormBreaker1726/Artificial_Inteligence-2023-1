#include "IDAStar.hpp"

IDAStar::IDAStar(std::shared_ptr<Board> b_initial)
{
    this->_board = std::make_shared<Board>(b_initial);

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

bool IDAStar::solver()
{
    unsigned int threshold = this->_board->h1();

    cost = 0;

    visited_nodes = 0;

    expanded_nodes = 0;

    this->_open_set.push(std::make_shared<PuzzleNode_stars>(this->_board));
    this->_open_set.top()->depth = 0;

    while (!this->_open_set.empty())
    {
        std::shared_ptr<PuzzleNode_stars> current_node = this->_open_set.top();
        this->_open_set.pop();

        if (current_node->_state->goal_state_reached())
        {
            std::cout << "Objective reached!" << std::endl;
            std::cout << "Moves:" << std::endl;
            current_node->_state->print_moves_map();
            std::cout << "Depth: " << current_node->depth << std::endl;
            std::cout << "Expanded nodes: " << expanded_nodes << std::endl;
            std::cout << "Visited nodes: " << visited_nodes << std::endl;
            std::cout << "Cost:" << current_node->g << std::endl;
            // current_node->_state->print();
            return true;
        }

        std::string current_state_str = current_node->_state->to_string();

        if (this->_closed_set.find(current_state_str) != this->_closed_set.end())
        {
            continue;
        }

        this->_closed_set.insert(current_state_str);

        unsigned int next_threshold = UINT32_MAX;

        std::vector<std::shared_ptr<Board>> next_boards = this->sucessors(current_node->_state);

        for (std::shared_ptr<Board> next_board : next_boards)
        {
            std::shared_ptr<PuzzleNode_stars> next_node = std::make_shared<PuzzleNode_stars>(next_board, current_node);

            next_node->g     = current_node->g + 1;
            next_node->h     = next_node->_state->calculate_h1();
            next_node->f     = next_node->g + next_node->h;
            next_node->depth = current_node->depth + 1;

            if (next_node->f > threshold)
            {
                next_threshold = std::min(next_threshold, next_node->f);
            }
            else
            {
                this->_open_set.push(next_node);
            }
            visited_nodes++;
        }

        threshold = next_threshold;
        expanded_nodes++;

        // std::cout << "Open set size = " << this->_open_set.size() << std::endl;
    }

    return false;
}

std::vector<std::shared_ptr<Board>> IDAStar::sucessors(std::shared_ptr<Board> b)
{
    std::vector<std::shared_ptr<Board>> _succss;

    size_t rank = b->rank();

    size_t empy_row    = b->empty_position().first;
    size_t empy_column = b->empty_position().second;

    if (empy_row > 0)
    {
        std::shared_ptr<Board> success_board = std::make_shared<Board>(b);
        success_board->move_up();

        _succss.push_back(success_board);
    }

    if (empy_row < rank - 1)
    {
        std::shared_ptr<Board> success_board = std::make_shared<Board>(b);
        success_board->move_down();

        _succss.push_back(success_board);
    }

    if (empy_column < rank - 1)
    {
        std::shared_ptr<Board> success_board = std::make_shared<Board>(b);
        success_board->move_right();

        _succss.push_back(success_board);
    }

    if (empy_column > 0)
    {
        std::shared_ptr<Board> success_board = std::make_shared<Board>(b);
        success_board->move_left();

        _succss.push_back(success_board);
    }

    return _succss;
}
