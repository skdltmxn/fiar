#pragma once
#ifndef CONNECT4GAME_H
#define CONNECT4GAME_H

class Connect4Game
{
private:
	int board[7][7];   // to create a 7 * 7 board
	int turn;        // to toggle the turn of the players
public:
	Connect4Game();     // constructor
	void showBoard();    // to show board
	void switchTurn();     // to toggle the turns
	bool Won();             // to check whether any one win or not
	bool BoardFull();     // to check whether the board is full or not
	void start();              // the starter of the game
	~Connect4Game();
};
#endif
