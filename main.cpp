#include "fiar.h"
#include <iostream>

int main()
{
    fiar game;

    // start game and put my stone if my turn
    game.start();

    while (game.is_playing())
    {
        // get opponent's col #
        int col = game.get_opponent_col();

        // put stone on gameboard
        game.put_stone(col);

        // think next stone (heuristic / input)
        game.think();
    }

	switch (game.result())
	{
	case fiar::GAME_RESULT::WIN:
		std::cout << "You won!" << std::endl;
		break;
	case fiar::GAME_RESULT::LOSE:
		std::cout << "You lost!" << std::endl;
		break;
	case fiar::GAME_RESULT::DRAW:
		std::cout << "Draw game!" << std::endl;
		break;
	}

    return 0;
}
