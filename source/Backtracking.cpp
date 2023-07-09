#include "Backtracking.hpp"

Backtracking::Backtracking(Board *initial)
{
    this->_initial_board   = initial;
    PuzzleNode_stars *root = new PuzzleNode_stars(this->_initial_board);
    root->depth            = 0;

    this->_solution_stack.push(root);
    this->_visited_nodes.insert(this->_initial_board->to_string());

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

Backtracking::~Backtracking()
{
    while (!this->_solution_stack.empty())
    {
        PuzzleNode_stars *node = this->_solution_stack.top();
        this->_solution_stack.pop();
        delete node;
    }
}

bool Backtracking::solver()
{
    while (!this->_solution_stack.empty())
    {
        PuzzleNode_stars *current_node = this->_solution_stack.top();
        this->_solution_stack.pop();

        if (current_node->_state->goal_state_reached())
        {
            std::cout << "Objective reached!" << std::endl;
            std::cout << "Moves:" << std::endl;
            current_node->_state->print_moves_map();
            std::cout << "Depth: " << current_node->depth << std::endl;
            current_node->_state->print();
            delete current_node;
            return true;
        }

        Board *current_board = new Board(current_node->_state);

        size_t rank = current_board->rank();

        size_t empy_row    = current_board->empty_position().first;
        size_t empy_column = current_board->empty_position().second;

        if (empy_row > 0)
        {
            // up

            Board *new_board = new Board(current_board);
            new_board->move_up();

            if (!this->is_visited(new_board->to_string()))
            {
                PuzzleNode_stars *new_node = new PuzzleNode_stars(new_board, current_node, "Up");
                new_node->depth            = current_node->depth + 1;
                this->_solution_stack.push(new_node);
                this->_visited_nodes.insert(new_board->to_string());
            }
            else
            {
                delete new_board;
            }
        }

        if (empy_row < rank - 1)
        {
            // down

            Board *new_board = new Board(current_board);
            new_board->move_down();

            if (!this->is_visited(new_board->to_string()))
            {
                PuzzleNode_stars *new_node = new PuzzleNode_stars(new_board, current_node, "Down");
                new_node->depth            = current_node->depth + 1;
                this->_solution_stack.push(new_node);
                this->_visited_nodes.insert(new_board->to_string());
            }
            else
            {
                delete new_board;
            }
        }

        if (empy_column < rank - 1)
        {
            // right

            Board *new_board = new Board(current_board);
            new_board->move_right();

            if (!this->is_visited(new_board->to_string()))
            {
                PuzzleNode_stars *new_node = new PuzzleNode_stars(new_board, current_node, "Right");
                new_node->depth            = current_node->depth + 1;
                this->_solution_stack.push(new_node);
                this->_visited_nodes.insert(new_board->to_string());
            }
            else
            {
                delete new_board;
            }
        }

        if (empy_column > 0)
        {
            // left
            Board *new_board = new Board(current_board);
            new_board->move_left();

            if (!this->is_visited(new_board->to_string()))
            {
                PuzzleNode_stars *new_node = new PuzzleNode_stars(new_board, current_node, "Left");
                new_node->depth            = current_node->depth + 1;
                this->_solution_stack.push(new_node);
                this->_visited_nodes.insert(new_board->to_string());
            }
            else
            {
                delete new_board;
            }
        }

        delete current_board;
    }
    return false;
}

bool Backtracking::is_visited(std::string b)
{
    return this->_visited_nodes.find(b) != this->_visited_nodes.end();
}

void Backtracking::do_backtrack(PuzzleNode_stars *current_node)
{
}
