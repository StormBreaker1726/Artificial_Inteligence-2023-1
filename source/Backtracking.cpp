#include "Backtracking.hpp"

Backtracking::Backtracking(std::shared_ptr<Board> initial)
{
    this->_initial_board                   = initial;
    std::shared_ptr<PuzzleNode_stars> root = std::make_shared<PuzzleNode_stars>(this->_initial_board);
    root->depth                            = 0;

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
        if (this->iterations == LIM)
            printf("Iteration limit!\n");
        printf("Time spent in the algorithm: %e seconds\n", (end - start));
    }
}

Backtracking::~Backtracking()
{
}

bool Backtracking::solver()
{
    this->iterations = 0;

    this->max_depth = 0;

    cost           = 0;
    visited_nodes  = 0;
    expanded_nodes = 0;

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
            std::cout << "Expanded nodes: " << expanded_nodes << std::endl;
            std::cout << "Visited nodes: " << visited_nodes << std::endl;
            std::cout << "Cost of solution: " << current_node->depth << std::endl;
            std::cout << "Branching factor: " << ((float)visited_nodes / (float)max_depth) << std::endl;
            // current_node->_state->print();
            // delete current_node;
            return true;
        }

        expanded_nodes++;

        std::shared_ptr<Board> current_board = std::make_shared<Board>(current_node->_state);

        size_t rank = current_board->rank();

        size_t empy_row    = current_board->empty_position().first;
        size_t empy_column = current_board->empty_position().second;

        if (empy_row > 0)
        {
            // up

            std::shared_ptr<Board> new_board = std::make_shared<Board>(current_board);
            new_board->move_up();

            if (!this->is_visited(new_board->to_string()))
            {
                std::shared_ptr<PuzzleNode_stars> new_node = std::make_shared<PuzzleNode_stars>(new_board, current_node, "Up");
                new_node->depth                            = current_node->depth + 1;
                this->max_depth                            = std::max(this->max_depth, new_node->depth);
                this->_solution_stack.push(new_node);
                this->_visited_nodes.insert(new_board->to_string());
                visited_nodes++;
            }
        }

        if (empy_row < rank - 1)
        {
            // down

            std::shared_ptr<Board> new_board = std::make_shared<Board>(current_board);
            new_board->move_down();

            if (!this->is_visited(new_board->to_string()))
            {
                std::shared_ptr<PuzzleNode_stars> new_node = std::make_shared<PuzzleNode_stars>(new_board, current_node, "Down");
                new_node->depth                            = current_node->depth + 1;
                this->max_depth                            = std::max(this->max_depth, new_node->depth);
                this->_solution_stack.push(new_node);
                this->_visited_nodes.insert(new_board->to_string());
                visited_nodes++;
            }
        }

        if (empy_column < rank - 1)
        {
            // right

            std::shared_ptr<Board> new_board = std::make_shared<Board>(current_board);
            new_board->move_right();

            if (!this->is_visited(new_board->to_string()))
            {
                std::shared_ptr<PuzzleNode_stars> new_node = std::make_shared<PuzzleNode_stars>(new_board, current_node, "Right");
                new_node->depth                            = current_node->depth + 1;
                this->max_depth                            = std::max(this->max_depth, new_node->depth);
                this->_solution_stack.push(new_node);
                this->_visited_nodes.insert(new_board->to_string());
                visited_nodes++;
            }
        }

        if (empy_column > 0)
        {
            // left
            std::shared_ptr<Board> new_board = std::make_shared<Board>(current_board);
            new_board->move_left();

            if (!this->is_visited(new_board->to_string()))
            {
                std::shared_ptr<PuzzleNode_stars> new_node = std::make_shared<PuzzleNode_stars>(new_board, current_node, "Left");
                new_node->depth                            = current_node->depth + 1;
                this->max_depth                            = std::max(this->max_depth, new_node->depth);
                this->_solution_stack.push(new_node);
                this->_visited_nodes.insert(new_board->to_string());
                visited_nodes++;
            }
        }
    }
    return false;
}

bool Backtracking::is_visited(std::string b)
{
    return this->_visited_nodes.find(b) != this->_visited_nodes.end();
}
