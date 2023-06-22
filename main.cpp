#include "includes.hpp"
#include "AStar.hpp"

int main(int argc, char **argv)
{
    std::ifstream instance;
    instance.open(argv[1]);

    Board *b = new Board(instance);

    std::cout << "\nh1 = " << b->h1() << std::endl;

    b->print_moves_map();

    AStar a(b);

    return 0;
}