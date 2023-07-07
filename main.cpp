#include "AStar.hpp"
#include "IDAStar.hpp"
#include "includes.hpp"

int main(int argc, char **argv)
{
    std::ifstream instance;
    instance.open(argv[1]);

    Board *b = new Board(instance);

    b->print();

    // std::cout << "\n\n";

    // std::cout << b->to_string() << std::endl;

    IDAStar alg(b);

    return 0;
}