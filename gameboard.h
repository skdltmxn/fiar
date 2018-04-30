#pragma once

#include "stone.h"
#include <iostream>
#include <memory>

class gameboard
{
public:
    void init()
    {
        for (auto& row : _stones)
            for (auto& col : row)
                col.reset(nullptr);
    }

    bool is_available(int col) const
    {
        for (auto& row : _stones)
        {
            if (row[col - 1] == nullptr)
                return true;
        }

        return false;
    }

    void add_stone(bool mine, int col)
    {
        for (auto& row : _stones)
        {
            if (row[col - 1] == nullptr)
            {
                row[col - 1] = std::make_unique<stone>(mine);
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
                std::cout << " " << (col ? col->symbol() : '.') << " ";

            std::cout << std::endl;
        }
    }

private:
    // 6 rows, 7 cols
    // row 0 is the bottom-most row (stone gets piled up from row 0)
    std::unique_ptr<stone> _stones[6][7];
};
