#include "AStar.hpp"
#include "includes.hpp"

int main(int argc, char **argv)
{
    std::ifstream instance;
    instance.open(argv[1]);

    Board *b = new Board(instance);

    AStar a(b);

    return 0;
}