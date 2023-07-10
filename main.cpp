#include "AStar.hpp"
#include "BFS.hpp"
#include "Backtracking.hpp"
#include "Board.hpp"
#include "DFS.hpp"
#include "Greedy.hpp"
#include "IDAStar.hpp"
#include "UniformCost.hpp"
#include "includes.hpp"

void astar(std::shared_ptr<Board> b);
void idastar(std::shared_ptr<Board> b);
void bfs(std::shared_ptr<Board> b);
void dfs(std::shared_ptr<Board> b);
void uc(std::shared_ptr<Board> b);
void bkt(std::shared_ptr<Board> b);
void greedy(std::shared_ptr<Board> b);

int main(int argc, char **argv)
{
    std::ifstream instance;
    instance.open(argv[1]);

    std::shared_ptr<Board> b = std::make_shared<Board>(instance);

    b->print();

    switch (atoi(argv[2]))
    {
        case 1:
            astar(b);
            break;
        case 2:
            idastar(b);
            break;
        case 3:
            uc(b);
            break;
        case 4:
            bfs(b);
            break;
        case 5:
            dfs(b);
            break;
        case 6:
            bkt(b);
            break;
        case 7:
            greedy(b);
            break;

        default:
            break;
    }

    return 0;
}

void astar(std::shared_ptr<Board> b)
{
    std::cout << "\nA*:" << std::endl;
    AStar ast(b);
}

void idastar(std::shared_ptr<Board> b)
{
    std::cout << "\nIDA*:" << std::endl;
    IDAStar idast(b);
}

void bfs(std::shared_ptr<Board> b)
{
    std::cout << "\nBFS:" << std::endl;
    BFS bfss(b);
}

void dfs(std::shared_ptr<Board> b)
{
    std::cout << "\nDFS:" << std::endl;
    DFS dfss(b);
}

void uc(std::shared_ptr<Board> b)
{
    std::cout << "\nUniform Cost:" << std::endl;
    UniformCost unic(b);
}

void bkt(std::shared_ptr<Board> b)
{
    std::cout << "\nBacktracking:" << std::endl;
    Backtracking bkt(b);
}

void greedy(std::shared_ptr<Board> b)
{
    std::cout << "\nGreedy:" << std::endl;
    Greedy greed(b);
}