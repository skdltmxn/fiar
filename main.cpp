#include "fiar.h"
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")

int main()
{
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

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

	WSACleanup();

    return 0;
}
