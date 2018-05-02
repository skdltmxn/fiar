#pragma once

#include <iostream>
#include <memory>

#define ROW 6
#define COL 7

template <typename T>
inline T max(T a, T b)
{
    return (a > b) ? a : b;
}

template <typename T>
inline T min(T a, T b)
{
    return (a < b) ? a : b;
}

class gameboard
{
public:
    void init()
    {
        for (auto& row : _board)
            for (auto& col : row)
                col = 0;

        _moves = 0;
    }

    bool is_full() const
    {
        return _moves >= ROW * COL;
    }

    bool is_available(int col) const
    {
        for (auto& row : _board)
        {
            if (row[col - 1] == 0)
                return true;
        }

        return false;
    }

    bool has_winning_lines(int row, int col) const
    {
        char last = 0;
        int count = 0;

        // check horizontal line
        auto horizontal_line = _board[row - 1];

        for (int i = 0; i < COL; ++i)
        {
            if (!horizontal_line[i])
            {
                count = 0;
                continue;
            }

            if (horizontal_line[i] == last)
                ++count;
            else
            {
                last = horizontal_line[i];
                count = 1;
            }

            if (count == 4)
                return true;
        }

        last = 0;
        count = 0;

        // check vertical line
        for (int i = 0; i < ROW; ++i)
        {
            if (!_board[i][col - 1])
            {
                count = 0;
                continue;
            }

            if (_board[i][col - 1] == last)
                ++count;
            else
            {
                last = _board[i][col - 1];
                count = 1;
            }

            if (count == 4)
                return true;
        }

        // check diagonal to NE
        last = 0;
        count = 0;
        int delta = min(col, row);
        int r = row - delta;
        int c = col - delta;
        
        while (r < ROW && c < COL)
        {
            if (!_board[r][c])
            {
                count = 0;
                ++r;
                ++c;
                continue;
            }

            if (_board[r][c] == last)
                ++count;
            else
            {
                last = _board[r][c];
                count = 1;
            }

            if (count == 4)
                return true;

            ++r;
            ++c;
        }

        // check diagonal to SE
        last = 0;
        count = 0;
        delta = min(col, ROW - row);
        r = row + delta;
        c = col - delta;

        while (r >= 0 && c < COL)
        {
            if (!_board[r][c])
            {
                count = 0;
                --r;
                ++c;
                continue;
            }

            if (_board[r][c] == last)
                ++count;
            else
            {
                last = _board[r][c];
                count = 1;
            }

            if (count == 4)
                return true;

            --r;
            ++c;
        }

        return false;
    }

    int add_stone(bool mine, int col)
    {
        for (int row = 0; row < ROW; ++row)
        {
            if (_board[row][col - 1] == 0)
            {
                _board[row][col - 1] = mine ? 1 : -1;
                ++_moves;
                return row + 1;
            }
        }

        return -1;
    }

    void draw_board() const
    {
        // draw current gameboard
        for (int row = 5; row > -1; --row)
        {
            for (auto& col : _board[row])
                std::cout << " " << (col ? (col == 1 ? 'O' : 'X') : '.') << " ";

            std::cout << std::endl;
        }
    }

private:
    // 6 rows, 7 cols
    // row 0 is the bottom-most row (stone gets piled up from row 0)
    char _board[ROW][COL];
    int _moves;
};
