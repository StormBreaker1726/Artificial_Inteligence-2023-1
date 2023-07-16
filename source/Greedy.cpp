#include "Greedy.hpp"

Greedy::Greedy(std::shared_ptr<Board> initial)
{
    this->_initial_board = std::make_shared<Board>(initial);

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

Greedy::~Greedy()
{
    // while (!this->_open_list.empty())
    // {
    //     PuzzleNode_stars *node = this->_open_list.top();
    //     this->_open_list.pop();
    //     delete node;
    // }
}

bool Greedy::solver()
{
    this->max_depth                                = 0;
    std::shared_ptr<PuzzleNode_stars> initial_node = std::make_shared<PuzzleNode_stars>(this->_initial_board);
    initial_node->depth                            = 0;
    this->_open_list.push(initial_node);

    cost           = 0;
    visited_nodes  = 0;
    expanded_nodes = 0;

    while (!this->_open_list.empty())
    {
        std::shared_ptr<PuzzleNode_stars> current_node = this->_open_list.top();
        this->_open_list.pop();

        if (current_node->_state->goal_state_reached())
        {
            expanded_nodes = _explored_set.size();
            visited_nodes  = expanded_nodes + _open_list.size();

            std::cout << "Objective reached!" << std::endl;
            std::cout << "Moves:" << std::endl;
            current_node->_state->print_moves_map();
            std::cout << "Depth: " << current_node->depth << std::endl;
            std::cout << "Expanded nodes: " << expanded_nodes << std::endl;
            std::cout << "Visited nodes: " << visited_nodes << std::endl;
            std::cout << "Cost:" << current_node->g << std::endl;
            std::cout << "Branching factor: " << ((float)visited_nodes / (float)max_depth) << std::endl;
            // current_node->_state->print();
            return true;
        }

        this->successors(current_node);
        this->_explored_set.insert(current_node->_state->to_string());
    }

    return false;
}

bool Greedy::is_explored(std::shared_ptr<Board> b)
{
    return (this->_explored_set.find(b->to_string()) != this->_explored_set.end());
}

void Greedy::successors(std::shared_ptr<PuzzleNode_stars> node)
{
    std::shared_ptr<Board> _current_state = node->_state;

    size_t rank = _current_state->rank();

    size_t empy_row    = _current_state->empty_position().first;
    size_t empy_column = _current_state->empty_position().second;

    if (empy_row > 0)
    {
        // up
        std::shared_ptr<Board> success_board = std::make_shared<Board>(_current_state);
        success_board->move_up();

        if (!this->is_explored(success_board))
        {
            std::shared_ptr<PuzzleNode_stars> child = this->create_child_node(success_board, node, "Up");
            this->_open_list.push(child);
        }
    }

    if (empy_row < rank - 1)
    {
        // down
        std::shared_ptr<Board> success_board = std::make_shared<Board>(_current_state);
        success_board->move_down();

        if (!this->is_explored(success_board))
        {
            std::shared_ptr<PuzzleNode_stars> child = this->create_child_node(success_board, node, "Down");
            this->_open_list.push(child);
        }
    }

    if (empy_column < rank - 1)
    {
        // right
        std::shared_ptr<Board> success_board = std::make_shared<Board>(_current_state);
        success_board->move_right();

        if (!this->is_explored(success_board))
        {
            std::shared_ptr<PuzzleNode_stars> child = this->create_child_node(success_board, node, "Right");
            this->_open_list.push(child);
        }
    }

    if (empy_column > 0)
    {
        // left
        std::shared_ptr<Board> success_board = std::make_shared<Board>(_current_state);
        success_board->move_left();

        if (!this->is_explored(success_board))
        {
            std::shared_ptr<PuzzleNode_stars> child = this->create_child_node(success_board, node, "Left");
            this->_open_list.push(child);
        }
    }
}

std::shared_ptr<PuzzleNode_stars> Greedy::create_child_node(std::shared_ptr<Board> board, std::shared_ptr<PuzzleNode_stars> parent, std::string move)
{
    std::shared_ptr<PuzzleNode_stars> child = std::make_shared<PuzzleNode_stars>(board, parent, move);
    child->g                                = parent->g + 1;
    child->h                                = board->h1();
    child->f                                = child->g + child->h;
    child->depth                            = parent->depth + 1;
    this->max_depth                         = std::max(this->max_depth, child->depth);
    return child;
}