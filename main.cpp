#include "includes.hpp"
#include "Board.hpp"

int main(int argc, char **argv)
{
    std::ifstream instance;
    instance.open(argv[1]);

    Board b(instance);

    std::cout << "\nh1 = " << b.h1() << std::endl;

    b.print_moves_map();

    return 0;
}