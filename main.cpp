#include "AStar.hpp"
#include "BFS.hpp"
#include "Backtracking.hpp"
#include "DFS.hpp"
#include "Greedy.hpp"
#include "IDAStar.hpp"
#include "UniformCost.hpp"
#include "includes.hpp"

void astar(Board *b);
void idastar(Board *b);
void bfs(Board *b);
void dfs(Board *b);
void uc(Board *b);
void bkt(Board *b);
void greedy(Board *b);

int main(int argc, char **argv)
{
    std::ifstream instance;
    instance.open(argv[1]);

    Board *b = new Board(instance);

    b->print();

    // std::cout << "\n\n";

    // std::cout << b->to_string() << std::endl;

    std::cout << "\nTesting..." << std::endl;

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

    delete b;

    // TODO implementar as duas métricas que faltam e criar o modelo de teste para facilitar na hr de fazer os testes finais

    return 0;
}

void astar(Board *b)
{
    std::cout << "\nA*:" << std::endl;
    AStar ast(b);
}

void idastar(Board *b)
{
    std::cout << "\nIDA*:" << std::endl;
    IDAStar idast(b);
}

void bfs(Board *b)
{
    std::cout << "\nBFS:" << std::endl;
    BFS bfss(b);
}

void dfs(Board *b)
{
    std::cout << "\nDFS:" << std::endl;
    DFS dfss(b);
}

void uc(Board *b)
{
    std::cout << "\nUniform Cost:" << std::endl;
    UniformCost unic(b);
}

void bkt(Board *b)
{
    std::cout << "\nBacktracking:" << std::endl;
    Backtracking bkt(b);
}

void greedy(Board *b)
{
    std::cout << "\nGreedy:" << std::endl;
    Greedy greed(b);
}