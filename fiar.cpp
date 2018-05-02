#include "fiar.h"
#include <iostream>
#include <string>

void fiar::start()
{
    // initialize gameboard
    _gameboard.init();

    char c;
    std::cout << "My turn first? (y/n) > ";
    std::cin >> c;

    if (c == 'y' || c == 'Y')
        _myturn = true;
    else
        _myturn = false;

    if (_myturn)
        think(); // think next stone
}

bool fiar::is_playing() const
{
    return true;
}

int fiar::get_opponent_col() const
{
    int col = 0;

    while (1)
    {
        std::cout << "Choose opponent's stone col # (1 ~ 7) => ";
        std::cin >> col;

        if (col < 1 || col > 7)
        {
            std::cerr << "Invalid value!" << std::endl;
            continue;
        }

        break;
    }

    return col;
}

void fiar::put_stone(int col)
{
    if (!_gameboard.is_available(col))
    {
        std::cerr << "col " << col << " is full of stones!" << std::endl;
        return;
    }

    _gameboard.add_stone(_myturn, col);
    _gameboard.draw_board();

    _myturn = !_myturn;
}

void fiar::think()
{
    std::cout << "Choose algorithm (1. heuristic / 2. rule) => ";
    int c;
    std::cin >> c;

    int col;
    switch (c)
    {
    default:
    case 1:
        // use heuristic
        col = _think_heuristic();
        break;

    case 2:
        // use rule
        col = _think_rule();
        break;
    }

    put_stone(col);
}

// think using heuristic
// we use negamax, a variant of minmax algorithm and alpha-beta pruning
int fiar::_think_heuristic() const
{
    return 4;
}

int fiar::_think_rule() const
{
    return 4;
}
