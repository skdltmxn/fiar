#pragma once

#include <iostream>
#include <memory>

#define ROW 6
#define COL 7

class gameboard
{
public:
    void init()
    {
        for (auto& row : _stones)
            for (auto& col : row)
                col = 0;

        _moves = 0;
    }

    bool is_full() const
    {
        return _moves >= ROW * COL
    }

    bool is_available(int col) const
    {
        for (auto& row : _stones)
        {
            if (row[col - 1] == 0)
                return true;
        }

        return false;
    }

    void add_stone(bool mine, int col)
    {
        for (auto& row : _stones)
        {
            if (row[col - 1] == 0)
            {
                row[col - 1] = mine ? 1 : -1;
                ++_moves;
                return;
            }
        }
    }

    void draw_board() const
    {
        // draw current gameboard
        for (int row = 5; row > -1; --row)
        {
            for (auto& col : _stones[row])
                std::cout << " " << (col ? (col == 1 ? 'O' : 'X') : '.') << " ";

            std::cout << std::endl;
        }
    }

private:
    // 6 rows, 7 cols
    // row 0 is the bottom-most row (stone gets piled up from row 0)
    char _stones[ROW][COL];
    int _moves;
};
