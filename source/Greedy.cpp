#include "Greedy.hpp"

Greedy::Greedy(Board *initial)
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

Greedy::~Greedy()
{
    while (!this->_open_list.empty())
    {
        PuzzleNode_stars *node = this->_open_list.top();
        this->_open_list.pop();
        delete node;
    }
}

bool Greedy::solver()
{
    PuzzleNode_stars *initial_node = new PuzzleNode_stars(this->_initial_board);
    initial_node->depth            = 0;
    this->_open_list.push(initial_node);

    while (!this->_open_list.empty())
    {
        PuzzleNode_stars *current_node = this->_open_list.top();
        this->_open_list.pop();

        if (current_node->_state->goal_state_reached())
        {
            std::cout << "Objective reached!" << std::endl;
            std::cout << "Moves:" << std::endl;
            current_node->_state->print_moves_map();
            std::cout << "Depth: " << current_node->depth << std::endl;
            // current_node->_state->print();
            return true;
        }

        this->successors(current_node);
        this->_explored_set.insert(current_node->_state->to_string());
    }

    return false;
}

bool Greedy::is_explored(Board *b)
{
    return (this->_explored_set.find(b->to_string()) != this->_explored_set.end());
}

void Greedy::successors(PuzzleNode_stars *node)
{
    Board *_current_state = node->_state;

    size_t rank = _current_state->rank();

    size_t empy_row    = _current_state->empty_position().first;
    size_t empy_column = _current_state->empty_position().second;

    if (empy_row > 0)
    {
        // up
        Board *success_board = new Board(_current_state);
        success_board->move_up();

        if (!this->is_explored(success_board))
        {
            PuzzleNode_stars *child = this->create_child_node(success_board, node, "Up");
            this->_open_list.push(child);
        }
        else
        {
            delete success_board;
        }
    }

    if (empy_row < rank - 1)
    {
        // down
        Board *success_board = new Board(_current_state);
        success_board->move_down();

        if (!this->is_explored(success_board))
        {
            PuzzleNode_stars *child = this->create_child_node(success_board, node, "Down");
            this->_open_list.push(child);
        }
        else
        {
            delete success_board;
        }
    }

    if (empy_column < rank - 1)
    {
        // right
        Board *success_board = new Board(_current_state);
        success_board->move_right();

        if (!this->is_explored(success_board))
        {
            PuzzleNode_stars *child = this->create_child_node(success_board, node, "Right");
            this->_open_list.push(child);
        }
        else
        {
            delete success_board;
        }
    }

    if (empy_column > 0)
    {
        // left
        Board *success_board = new Board(_current_state);
        success_board->move_left();

        if (!this->is_explored(success_board))
        {
            PuzzleNode_stars *child = this->create_child_node(success_board, node, "Left");
            this->_open_list.push(child);
        }
        else
        {
            delete success_board;
        }
    }
}

PuzzleNode_stars *Greedy::create_child_node(Board *board, PuzzleNode_stars *parent, std::string move)
{
    PuzzleNode_stars *child = new PuzzleNode_stars(board, parent, move);
    child->g                = parent->g + 1;
    child->h                = board->h1();
    child->f                = child->g + child->h;
    child->depth            = parent->depth + 1;
    return child;
}