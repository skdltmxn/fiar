#pragma once

#include "gameboard.h"

class fiar
{
public:
    void start();
    bool is_playing() const;
    int get_opponent_col() const;
    void put_stone(int col);
    void think();

private:
    int _think_heuristic() const;
    int _think_rule() const;

    gameboard _gameboard;
    bool _myturn;
};
