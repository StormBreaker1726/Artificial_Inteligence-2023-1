#pragma once

#include "Board.hpp"
#include "includes.hpp"

struct PuzzleNode_stars
{
    std::shared_ptr<Board>            _state;
    std::shared_ptr<PuzzleNode_stars> _parent;

    size_t depth;

    std::string _caused_move;

    unsigned int g;
    unsigned int h;
    unsigned int f;

    PuzzleNode_stars(std::shared_ptr<Board> puzzle, std::shared_ptr<PuzzleNode_stars> par = nullptr, std::string mv = "")
    {
        this->_state       = puzzle;
        this->_parent      = par;
        this->_caused_move = (mv);
        this->g            = 0;
        this->h            = 0;
        this->f            = 0;
        this->depth        = 0;
    }

    bool is_goal_state()
    {
        return (this->_state->h1() == 0);
    }
};

struct PuzzleNode_stars_comparator
{
    bool operator()(const std::shared_ptr<PuzzleNode_stars> a, const std::shared_ptr<PuzzleNode_stars> b) const
    {
        return a->f > b->f;
    }
};

struct PuzzleNode_stars_comparator_gf
{
    bool operator()(const std::shared_ptr<PuzzleNode_stars> a, const std::shared_ptr<PuzzleNode_stars> b) const
    {
        return (a->g + a->h) > (b->g + b->h);
    }
};

struct PuzzleNode_comparator
{
    bool operator()(const std::shared_ptr<PuzzleNode_stars> a, const std::shared_ptr<PuzzleNode_stars> b) const
    {
        return a->h > b->h;
    }
};