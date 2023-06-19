#include "Board.hpp"

Board::Board(std::ifstream &instance)
{
    instance >> this->rank;

    // std::cout << "Rank = " << this->rank << std::endl;

    // reads perfect board
    for (size_t i = 0; i < rank; i++)
    {
        std::vector<unsigned int> tmp;
        for (size_t j = 0; j < rank; j++)
        {
            // lembro que fazer o push_back no perfect position aqui
            unsigned int temp;
            instance >> temp;
            tmp.push_back(temp);
        }
        this->_perfect_board.push_back(tmp);
    }

    size_t qtd_elements = this->rank * this->rank;

    for (size_t i = 0; i < qtd_elements; i++)
    {
        for (size_t j = 0; j < this->rank; j++)
        {
            for (size_t k = 0; k < this->rank; k++)
            {
                if (this->_perfect_board.at(j).at(k) == i)
                {
                    std::pair<size_t, size_t> temp;
                    temp.first = j;
                    temp.second = k;
                    this->_perfect_positions.push_back(temp);
                    break;
                }
            }
        }
    }

    // reads working board
    for (size_t i = 0; i < rank; i++)
    {
        std::vector<unsigned int> tmp;
        for (size_t j = 0; j < rank; j++)
        {
            unsigned int temp;
            instance >> temp;
            if (temp == 0)
            {
                std::pair<size_t, size_t> ps;
                ps.first = i;
                ps.second = j;
                this->empty_position = ps;
            }
            tmp.push_back(temp);
        }
        this->_working_board.push_back(tmp);
    }

    this->calculate_h1();

    this->_moves.append("Original");

    // this->print();
}

void Board::move_up()
{
    size_t i;
    size_t j;

    i = this->empty_position.first;
    j = this->empty_position.second;

    size_t new_i;
    size_t new_j;

    new_i = i - 1;
    new_j = j;

    unsigned int element_to_change = this->_working_board.at(new_i).at(new_j);

    this->_working_board.at(i).at(j) = element_to_change;

    this->_working_board.at(new_i).at(new_j) = 0;

    this->empty_position.first = new_i;
    this->empty_position.second = new_j;

    this->calculate_h1();

    this->_moves.append(" -> Up");
}

void Board::move_down()
{
    size_t i;
    size_t j;

    i = this->empty_position.first;
    j = this->empty_position.second;

    size_t new_i;
    size_t new_j;

    new_i = i + 1;
    new_j = j;

    unsigned int element_to_change = this->_working_board.at(new_i).at(new_j);

    this->_working_board.at(i).at(j) = element_to_change;

    this->_working_board.at(new_i).at(new_j) = 0;

    this->empty_position.first = new_i;
    this->empty_position.second = new_j;

    this->calculate_h1();

    this->_moves.append(" -> Down");
}

void Board::move_right()
{
    size_t i;
    size_t j;

    i = this->empty_position.first;
    j = this->empty_position.second;

    size_t new_i;
    size_t new_j;

    new_i = i;
    new_j = j + 1;

    unsigned int element_to_change = this->_working_board.at(new_i).at(new_j);

    this->_working_board.at(i).at(j) = element_to_change;

    this->_working_board.at(new_i).at(new_j) = 0;

    this->empty_position.first = new_i;
    this->empty_position.second = new_j;

    this->calculate_h1();

    this->_moves.append(" -> Right");
}

void Board::move_left()
{
    size_t i;
    size_t j;

    i = this->empty_position.first;
    j = this->empty_position.second;

    size_t new_i;
    size_t new_j;

    new_i = i;
    new_j = j - 1;

    unsigned int element_to_change = this->_working_board.at(new_i).at(new_j);

    this->_working_board.at(i).at(j) = element_to_change;

    this->_working_board.at(new_i).at(new_j) = 0;

    this->empty_position.first = new_i;
    this->empty_position.second = new_j;

    this->calculate_h1();

    this->_moves.append(" -> Left");
}

unsigned int Board::calculate_h1()
{
    int perfect_row;
    int perfect_col;
    int working_row;
    int working_col;

    this->_h1 = 0;

    size_t qtd_elements = this->rank * this->rank;

    for (size_t i = 0; i < qtd_elements; i++)
    {
        for (size_t j = 0; j < this->_working_board.size(); j++)
        {
            for (size_t k = 0; k < this->_working_board.size(); k++)
            {
                if (this->_working_board.at(j).at(k) == i)
                {
                    working_row = j;
                    working_col = k;
                    break;
                }
            }
        }

        perfect_row = this->_perfect_positions.at(i).first;
        perfect_col = this->_perfect_positions.at(i).second;

        int dx = std::abs(perfect_row - working_row);
        int dy = std::abs(perfect_col - working_col);

        this->_h1 += dx + dy;
    }

    return this->_h1;
}

unsigned int Board::h1()
{
    return this->_h1;
}

void Board::print()
{
    // std::cout << "\nPerfect positions:" << std::endl;
    // for (size_t i = 0; i < this->_perfect_positions.size(); i++)
    // {
    //     std::cout << "Element " << i << ": rol = " << this->_perfect_positions.at(i).first << " col = " << this->_perfect_positions.at(i).second << std::endl;
    // }

    std::cout << "Empty position: "
              << "rol = " << this->empty_position.first << " col = " << this->empty_position.second << std::endl;

    std::cout << "\nPerfect board:" << std::endl;
    for (size_t i = 0; i < this->_perfect_board.size(); i++)
    {
        for (size_t j = 0; j < this->_perfect_board.size(); j++)
        {
            std::cout << this->_perfect_board.at(i).at(j) << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "\nWorking board:" << std::endl;
    for (size_t i = 0; i < this->_working_board.size(); i++)
    {
        for (size_t j = 0; j < this->_working_board.size(); j++)
        {
            std::cout << this->_working_board.at(i).at(j) << " ";
        }
        std::cout << std::endl;
    }
}

void Board::print_moves_map()
{
    std::cout << this->_moves << std::endl;
}
