#include "Board.hpp"

Board::Board(std::ifstream& instance)
{
    instance >> this->_rank;

    // std::cout << "_Rank = " << this->_rank << std::endl;

    // reads perfect board
    for (size_t i = 0; i < _rank; i++)
    {
        std::vector<unsigned int> tmp;
        for (size_t j = 0; j < _rank; j++)
        {
            // lembro que fazer o push_back no perfect position aqui
            unsigned int temp;
            instance >> temp;
            tmp.push_back(temp);
        }
        this->_perfect_board.push_back(tmp);
    }

    size_t qtd_elements = this->_rank * this->_rank;

    for (size_t i = 0; i < qtd_elements; i++)
    {
        for (size_t j = 0; j < this->_rank; j++)
        {
            for (size_t k = 0; k < this->_rank; k++)
            {
                if (this->_perfect_board.at(j).at(k) == i)
                {
                    std::pair<size_t, size_t> temp;
                    temp.first  = j;
                    temp.second = k;
                    this->_perfect_positions.push_back(temp);
                    break;
                }
            }
        }
    }

    // reads working board
    for (size_t i = 0; i < _rank; i++)
    {
        std::vector<unsigned int> tmp;
        for (size_t j = 0; j < _rank; j++)
        {
            unsigned int temp;
            instance >> temp;
            if (temp == 0)
            {
                std::pair<size_t, size_t> ps;
                ps.first              = i;
                ps.second             = j;
                this->_empty_position = ps;
            }
            tmp.push_back(temp);
        }
        this->_working_board.push_back(tmp);
    }

    this->calculate_h1();

    this->_moves.append("Original");

    // this->print();
}

Board::Board(std::shared_ptr<Board> b)
{
    this->_moves = (b->_moves);

    this->_working_board = b->_working_board;
    this->_perfect_board = b->_perfect_board;

    // this->_empty_position    = b->_empty_position;
    // this->_perfect_positions = b->_perfect_positions;

    this->_empty_position    = std::make_pair(b->_empty_position.first, b->_empty_position.second);
    this->_perfect_positions = b->_perfect_positions;

    this->_rank = b->_rank;

    this->calculate_h1();
}

void Board::move_up()
{
#ifdef DEBUG
    std::cout << "Moving up" << std::endl;
#endif
    size_t i;
    size_t j;

    i = this->_empty_position.first;
    j = this->_empty_position.second;

    size_t new_i;
    size_t new_j;

    new_i = i - 1;
    new_j = j;

    unsigned int element_to_change = this->_working_board.at(new_i).at(new_j);

    this->_working_board.at(i).at(j) = element_to_change;

    this->_working_board.at(new_i).at(new_j) = 0;

    this->_empty_position.first  = new_i;
    this->_empty_position.second = new_j;

    this->calculate_h1();

    this->_moves.append(" -> Up");
}

void Board::move_down()
{
#ifdef DEBUG
    std::cout << "Moving down" << std::endl;
#endif
    size_t i;
    size_t j;

    i = this->_empty_position.first;
    j = this->_empty_position.second;

    size_t new_i;
    size_t new_j;

    new_i = i + 1;
    new_j = j;

    unsigned int element_to_change = this->_working_board.at(new_i).at(new_j);

    this->_working_board.at(i).at(j) = element_to_change;

    this->_working_board.at(new_i).at(new_j) = 0;

    this->_empty_position.first  = new_i;
    this->_empty_position.second = new_j;

    this->calculate_h1();

    this->_moves.append(" -> Down");
}

void Board::move_right()
{
#ifdef DEBUG
    std::cout << "Moving right" << std::endl;
#endif
    size_t i;
    size_t j;

    i = this->_empty_position.first;
    j = this->_empty_position.second;

    size_t new_i;
    size_t new_j;

    new_i = i;
    new_j = j + 1;

    unsigned int element_to_change = this->_working_board.at(new_i).at(new_j);

    this->_working_board.at(i).at(j) = element_to_change;

    this->_working_board.at(new_i).at(new_j) = 0;

    this->_empty_position.first  = new_i;
    this->_empty_position.second = new_j;

    this->calculate_h1();

    this->_moves.append(" -> Right");
}

void Board::move_left()
{
#ifdef DEBUG
    std::cout << "Moving left" << std::endl;
#endif
    size_t i;
    size_t j;

    i = this->_empty_position.first;
    j = this->_empty_position.second;

    size_t new_i;
    size_t new_j;

    new_i = i;
    new_j = j - 1;

    unsigned int element_to_change = this->_working_board.at(new_i).at(new_j);

    this->_working_board.at(i).at(j) = element_to_change;

    this->_working_board.at(new_i).at(new_j) = 0;

    this->_empty_position.first  = new_i;
    this->_empty_position.second = new_j;

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

    size_t qtd_elements = this->_rank * this->_rank;

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
    std::cout << "\nEmpty position: "
              << "\n\trol = " << this->_empty_position.first << " col = " << this->_empty_position.second << std::endl;

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
    std::cout << "\t" << this->_moves << std::endl;
}

bool Board::goal_state_reached()
{
    for (size_t i = 0; i < this->_working_board.size(); i++)
    {
        for (size_t j = 0; j < this->_working_board.at(i).size(); j++)
        {
            if (this->_perfect_positions.at(this->_working_board.at(i).at(j)).first != i ||
                this->_perfect_positions.at(this->_working_board.at(i).at(j)).second != j)
            {
                return false;
            }
        }
    }

    return true;
}

bool Board::equals(std::shared_ptr<Board> b)
{
    for (size_t i = 0; i < this->_working_board.size(); i++)
    {
        for (size_t j = 0; j < this->_working_board.at(i).size(); j++)
        {
            for (size_t k = 0; k < b->_working_board.size(); k++)
            {
                for (size_t l = 0; l < b->_working_board.at(k).size(); l++)
                {
                    if (this->_perfect_board.at(k).at(l) != this->_working_board.at(i).at(j))
                    {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

std::string Board::to_string()
{
    std::string board_string;
    for (size_t i = 0; i < _working_board.size(); i++)
    {
        for (size_t j = 0; j < _working_board[i].size(); j++)
        {
            board_string += std::to_string(_working_board[i][j]) + " ";
        }
        board_string += "\n";
    }
    return board_string;
}
