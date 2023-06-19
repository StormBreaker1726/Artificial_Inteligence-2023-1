#include "includes.hpp"
#include "Board.hpp"

int main()
{
    std::ifstream instance;
    instance.open("/home/joao-ntb/Documents/Repositories/UFJF/Artificial_Inteligence-2023-1/instances/faceis/dumb.txt");

    Board b(instance);

    std::cout << "\nh1 = " << b.h1() << std::endl;

    b.print_moves_map();

    return 0;
}