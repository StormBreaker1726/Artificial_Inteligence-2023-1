#include "IDAStar.hpp"

IDAStar::IDAStar(Board *b_initial)
{
    this->_board = new Board(b_initial);

    this->start = omp_get_wtime();
    bool result = this->solver();
    this->end   = omp_get_wtime();

    this->visited_nodes = this->expanded_nodes = this->branching_sum = 0;

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

    this->_open_set.push(new PuzzleNode_stars(this->_board));
    this->_open_set.top()->depth = 0;

    while (!this->_open_set.empty())
    {
        PuzzleNode_stars *current_node = this->_open_set.top();
        this->_open_set.pop();

        if (current_node->_state->goal_state_reached())
        {
            std::cout << "Objective reached!" << std::endl;
            std::cout << "Moves:" << std::endl;
            current_node->_state->print_moves_map();
            std::cout << "Depth: " << current_node->depth << std::endl;
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

        std::vector<Board *> next_boards = this->sucessors(current_node->_state);

        for (Board *next_board : next_boards)
        {
            PuzzleNode_stars *next_node = new PuzzleNode_stars(next_board, current_node);

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
        }

        threshold = next_threshold;

        // std::cout << "Open set size = " << this->_open_set.size() << std::endl;
    }

    return false;
}

std::vector<Board *> IDAStar::sucessors(Board *b)
{
    std::vector<Board *> _succss;

    size_t rank = b->rank();

    size_t empy_row    = b->empty_position().first;
    size_t empy_column = b->empty_position().second;

    if (empy_row > 0)
    {
        Board *success_board = new Board(b);
        success_board->move_up();

        _succss.push_back(success_board);
    }

    if (empy_row < rank - 1)
    {
        Board *success_board = new Board(b);
        success_board->move_down();

        _succss.push_back(success_board);
    }

    if (empy_column < rank - 1)
    {
        Board *success_board = new Board(b);
        success_board->move_right();

        _succss.push_back(success_board);
    }

    if (empy_column > 0)
    {
        Board *success_board = new Board(b);
        success_board->move_left();

        _succss.push_back(success_board);
    }

    return _succss;
}
