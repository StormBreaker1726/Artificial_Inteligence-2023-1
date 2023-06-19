#pragma once

#include "includes.hpp"

class Board
{
public:
    Board(std::ifstream &instance);
    ~Board(){};

    void move_up();
    void move_down();
    void move_right();
    void move_left();

    unsigned int calculate_h1();

    unsigned int h1();

    void print();

    void print_moves_map();

private:
    std::vector<std::vector<unsigned int> > _working_board;
    std::vector<std::vector<unsigned int> > _perfect_board;

    std::string _moves;

    unsigned int _h1;

    std::ifstream instance;

    std::pair<size_t, size_t> empty_position;

    size_t rank;

    std::vector<std::pair<size_t, size_t> > _perfect_positions;
};