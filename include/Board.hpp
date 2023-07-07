#pragma once

#include "includes.hpp"

class Board
{
public:
    Board(std::ifstream& instance);
    Board(Board *b);
    ~Board(){};

    void move_up();
    void move_down();
    void move_right();
    void move_left();

    unsigned int calculate_h1();

    unsigned int h1();

    void print();

    void print_moves_map();

    inline size_t rank()
    {
        return this->_rank;
    };

    inline std::pair<size_t, size_t> empty_position()
    {
        return this->_empty_position;
    };

    bool goal_state_reached();

    bool equals(Board *b);

    std::string to_string();

private:
    std::vector<std::vector<unsigned int>> _working_board;
    std::vector<std::vector<unsigned int>> _perfect_board;

    std::string _moves;

    unsigned int _h1;

    std::ifstream instance;

    std::pair<size_t, size_t> _empty_position;

    size_t _rank;

    std::vector<std::pair<size_t, size_t>> _perfect_positions;
};