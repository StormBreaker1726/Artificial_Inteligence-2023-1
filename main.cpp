#include "AStar.hpp"
#include "BFS.hpp"
#include "Backtracking.hpp"
#include "DFS.hpp"
#include "Greedy.hpp"
#include "IDAStar.hpp"
#include "UniformCost.hpp"
#include "includes.hpp"

int main(int argc, char **argv)
{
    std::ifstream instance;
    instance.open(argv[1]);

    Board *b = new Board(instance);

    b->print();

    // std::cout << "\n\n";

    // std::cout << b->to_string() << std::endl;

    // IDAStar alg(b);

    // GreedyFirst alg(b);

    // Backtracking alg(b);

    // BFS alg(b);

    // DFS alg(b);

    // Greedy alg(b);

    return 0;
}