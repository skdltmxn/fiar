#pragma once

#include "gameboard.h"

class fiar
{
public:
	enum class GAME_RESULT
	{
		WIN,
		LOSE,
		DRAW,
	};

    void start();
    bool is_playing() const { return _playing; }
    int get_opponent_col() const;
    void put_stone(int col);
    void think();
	GAME_RESULT result() const { return _result; }

private:
    int think_heuristic();
	int maximize(int depth, int alpha, int beta, int &choice);
	int minimize(int depth, int alpha, int beta, int &choice);
    int think_rule();

	// rule functions


    gameboard _gameboard;
    bool _myturn;
    bool _playing;
	int _turn;
	GAME_RESULT _result;
};
