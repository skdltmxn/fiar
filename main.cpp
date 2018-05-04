#include "main.h";
#include <math.h>
#include <iostream>

int main()
{
	int counter = 0;
	int order = 1;
	bool winner = false;
	bool first = false;
	
	cout << "WHO FIRST? 1.RULE 2.USER : ";
	cin >> order;

	srand(GetTickCount());   //sets randomizer as time *unique*
	cout << "Please select a number from 1-7" << endl;
	cout << "| 1| 2| 3| 4| 5| 6| 7" << endl;
	cout << "---------------------";
	draw_board();

	for (int i = 0; i < 21; i++)
	{
		if (order == 1 && i == 0) first = true;
		else first = false;
		player_movement(1);
		draw_board();
		winner = check_for_winner(LastMoveX, LastMoveY, 1);
		evalutescore(1);
		evalutescore(2);
		for (int j = 0; j < 7; j++) {
			if (checknum[j] >= 6) {
				score[0][j] = score[1][j] = 0;
			}
		}
		cout << " " << abs(score[0][0] - score[1][0]) << "  " << abs(score[0][1] - score[1][1]) << "  "
			<< abs(score[0][2] - score[1][2]) << "  " << abs(score[0][3] - score[1][3])<< "  "
			<< abs(score[0][4] - score[1][4]) << "  " << abs(score[0][5] - score[1][5]) << "  " << abs(score[0][6] - score[1][6])<< endl;

		if (winner)
		{
			cout << "\nplayer Win" << endl;
			break;
		}

		player_movement(2);
		draw_board();
		winner = check_for_winner(LastMoveX, LastMoveY, 2);
		for (int j = 0; j < 7; j++) {
			if (checknum[j] >= 6) {
				score[0][j] = score[1][j] = 0;
			}
		}
		evalutescore(1);
		evalutescore(2);
		cout << abs(score[1][0] - score[0][0]) << " " << abs(score[1][1] - score[0][1]) << " "
			<< abs(score[1][2] - score[0][2]) << " " << abs(score[1][3] - score[0][3]) << " " 
			<< abs(score[1][4] - score[0][4]) << " " << abs(score[1][5] - score[0][5]) << " " << abs(score[1][6] - score[0][6]) << endl;
		if (winner)
		{
			cout << "\nYou Win" << endl;
			break;
		}
	}
	system("PAUSE");
	return 0;
}

void draw_board()
{
	cout << endl;

	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			cout << "| ";
			if (board_info[y][x] == 0) cout << " ";
			else if (board_info[y][x] == 1) cout << "X";
			else if (board_info[y][x] == 2) cout << "O";
		}
		cout << "\n---------------------" << endl;
	}
}

void player_movement(int player)
{
	int choice;
	cout << "\nPlayer" << player << ", please select a number from 1 - 7: ";
	cin >> choice;

	//Error Checking

	if (cin.fail())
	{
		cout << "Error!";
		exit(1);
	}

	while (choice > WIDTH || choice <= 0)
	{
		cout << "\nPlease select again: ";
		cin >> choice;
	}

	int number = 0;
	while (board_info[(HEIGHT - 1) - number][(choice - 1)] != 0)
	{
		number++;
		if (number > (HEIGHT - 1))
		{
			cout << "\nPlease select again: ";
			cin >> choice;
			number = 0;  //You must reset the number else it will start at the beginning of the array
		}
	};

	board_info[(HEIGHT - 1) - number][choice - 1] = player;
	LastMoveY = (HEIGHT - 1) - number;
	LastMoveX = choice - 1;
	current[LastMoveX] -= 1;
	checknum[LastMoveX] += 1;
	cout << "\nPlayer" << player << " " << LastMoveX << "," << LastMoveY;
}

bool check_for_winner(int x, int y, int player)
{
	bool winner;

	if (check_diagonal_combo_SW_NE(x, y, player)) return true;
	else if (check_diagonal_combo_NW_SE(x, y, player)) return true;
	else if (check_vertical_combo(x, y, player)) return true;
	else if (check_horizontal_combo(x, y, player)) return true;
	else return false;
}

bool check_diagonal_combo_SW_NE(int x, int y, int player)
{
	int score = 1;
	int count = 1;

	while ((y - count >= 0) && (x + count < WIDTH))
	{
		if (board_info[y - count][x+count] == player)  //Check sw to ne
		{
			score++;
			count++;
		}
		else break;
	}

	count = 1;
	while ((y + count < HEIGHT) && (x - count >= 0))
	{
		if (board_info[y + count][x - count] == player)  //Check ne to sw
		{
			score++;
			count++;
		}
		else break;
	}
	if (score == 4) return true;
	else {
		return false;
	}
}

bool check_diagonal_combo_NW_SE(int x, int y, int player)
{
	int score = 1;
	int count = 1;

	while ((y + count < HEIGHT) && (x + count < WIDTH))
	{
		if (board_info[y + count][x + count] == player)  //Check nw to se
		{
			score++;
			count++;
		}
		else break;
	}

	count = 1;
	while ((y - count >= 0) && (x - count >= 0))
	{
		if (board_info[y - count][x - count] == player)  //Check se to nw
		{
			score++;
			count++;
		}
		else break;
	}
	if (score == 4) return true;
	else {
		return false;
	}
}

bool check_vertical_combo(int x, int y, int player)
{
	int score = 1;
	int count = 1;

	while (y + count >= 0 && y + count < HEIGHT)
	{
		if (board_info[y + count][x] == player)  //Check Down
		{
			score++;
			count++;
		}
		else break;//If no combo is detected break from the loop
	}
	if (score == 4) return true;
	else {
		return false;
	}
}

bool check_horizontal_combo(int x, int y, int player)
{
	int score = 1;
	int count = 1;

	while ((x + count >= 0) && (x + count < WIDTH))
	{
		if (board_info[y][x + count] == player)  //Check Left
		{
			score++;
			count++;
		}
		else break;  //If no combo is detected break from the loop
	}

	count = 1;
	while ((x - count < WIDTH) && (x - count >= 0))
	{
		if (board_info[y][x - count] == player)  //Check Right
		{
			score++;
			count++;
		}
		else break;  //If no combo is detected break from the loop
	}
	if (score == 4) return true;
	else {
		return false;
	}
}

//This is my simple 'Connect4 Game'
//Two player game , no computer player

void evalutescore(int player) {
	score[2][7] = { 0 };
	if (player == 1) {
		for (int i = 0; i < 7; i++) {
			int j = current[i];
			//for(int j = 0; j<6; j++)
			if (board_info[j][i] == 0) {
				int count = 1;
				int blank = 0;
				int p1 = 0;
				int o1 = 0;
				while ((j - count >= 0) && (i + count < WIDTH) && count < 4)
				{
					if (board_info[j - count][i + count] == player)  //Check sw to ne
					{
						p1++;
						count++;
					}
					else if (board_info[j - count][i + count] == 0) {
						blank++;
						count++;
					}
					else {
						o1++;
						count++;
					}
				}

				count = 1;
				while ((j + count < HEIGHT) && (i - count >= 0) && count < 4)
				{
					if (board_info[j + count][i - count] == player)  //Check ne to sw
					{
						p1++;
						count++;
					}
					else if (board_info[j + count][i - count] == 0) {
						blank++;
						count++;
					}
					else {
						o1++;
						count++;
					}
				}
				if (p1 == 1 && blank >= 2) {
					score[0][i] += 5;
				}
				else if (p1 == 2 && blank >= 1) {
					score[0][i] += 300;
				}
				else if (p1 == 3 && blank >= 0) {
					score[0][i] += 10000;
				}

				blank = 0;
				p1 = 0;
				o1 = 0;
				count = 1;

				while ((j + count < HEIGHT) && (i + count < WIDTH) && count < 4)
				{
					if (board_info[j + count][i + count] == player)  //Check nw to se
					{
						p1++;
						count++;
					}
					else if (board_info[j + count][i + count] == 0) {
						blank++;
						count++;
					}
					else {
						o1++;
						count++;
					}
				}

				count = 1;
				while ((j - count >= 0) && (i - count >=0) && count < 4)
				{
					if (board_info[j - count][i - count] == player)  //Check se to nw
					{
						p1++;
						count++;
					}
					else if (board_info[j - count][i - count] == 0) {
						blank++;
						count++;
					}
					else {
						o1++;
						count++;
					}
				}
				if (p1 == 1 && blank >= 2) {
					score[0][i] += 5;
				}
				else if (p1 == 2 && blank >= 1) {
					score[0][i] += 300;
				}
				else if (p1 == 3 && blank >= 0) {
					score[0][i] += 10000;
				}

				blank = 0;
				p1 = 0;
				o1 = 0;
				count = 1;

				while (j + count >= 0 && j + count < HEIGHT && count < 4)
				{
					if (board_info[j + count][i] == player)  //Check down
					{
						p1++;
						count++;
					}
					else if (board_info[j + count][i] == 0) {
						blank++;
						count++;
					}
					else {
						o1++;
						count++;
					}
				}

				count = 1;
				while (j - count >= 0 && j - count < HEIGHT && count < 4)
				{
					if (board_info[j - count][i] == player)  //Check up
					{
						p1++;
						count++;
					}
					else if (board_info[j - count][i] == 0) {
						blank++;
						count++;
					}
					else {
						o1++;
						count++;
					}
				}

				if (p1 == 1 && blank >= 2) {
					score[0][i] += 5;
				}
				else if (p1 == 2 && blank >= 1) {
					score[0][i] += 300;
				}
				else if (p1 == 3 && blank >= 0) {
					score[0][i] += 10000;
				}

				blank = 0;
				p1 = 0;
				o1 = 0;
				count = 1;

				while ((i + count >= 0) && (i + count < WIDTH) && count < 4)
				{
					if (board_info[j][i + count] == player)  //Check left
					{
						p1++;
						count++;
					}
					else if (board_info[j][i + count] == 0) {
						blank++;
						count++;
					}
					else {
						o1++;
						count++;
					}
				}

				count = 1;
				while ((i - count >= 0) && (i - count < WIDTH) && count < 4)
				{
					if (board_info[j][i - count] == player)  //Check right
					{
						p1++;
						count++;
					}
					else if (board_info[j][i - count] == 0) {
						blank++;
						count++;
					}
					else {
						o1++;
						count++;
					}
				}
				if (p1 == 1 && blank >= 2) {
					score[0][i] += 5;
				}
				else if (p1 == 2 && blank >= 1) {
					score[0][i] += 300;
				}
				else if (p1 == 3 && blank >= 0) {
					score[0][i] += 10000;
				}
			}
			else if (board_info[j][i] == 1 || board_info[j][i] == 2);

		}
	}

	else if (player == 2) {
		for (int i = 0; i < 7; i++) {
			int j = current[i];
			//for(int j = 0; j<6; j++)
			if (board_info[j][i] == 0) {
				int count = 1;
				int blank = 0;
				int p1 = 0;
				int o1 = 0;
				while ((j - count >= 0) && (i + count < WIDTH) && count <= 4)
				{
					if (board_info[j - count][i + count] == player)  //Check sw to ne
					{
						p1++;
						count++;
					}
					else if (board_info[j - count][i + count] == 0) {
						blank++;
						count++;
					}
					else {
						o1++;
						count++;
					}
				}

				count = 1;
				while ((j + count < HEIGHT) && (i + count >= 0) && count <= 4)
				{
					if (board_info[j + count][i - count] == player)  //Check ne to sw
					{
						p1++;
						count++;
					}
					else if (board_info[j + count][i - count] == 0) {
						blank++;
						count++;
					}
					else {
						o1++;
						count++;
					}
				}
				if (p1 == 1 && blank >= 2) {
					score[1][i] += 5;
				}
				else if (p1 == 2 && blank >= 1) {
					score[1][i] += 300;
				}
				else if (p1 == 3 && blank >= 0) {
					score[1][i] += 10000;
				}

				blank = 0;
				p1 = 0;
				o1 = 0;
				count = 1;

				while ((j + count < HEIGHT) && (i + count < WIDTH) && count <= 4)
				{
					if (board_info[j + count][i + count] == player)  //Check nw to se
					{
						p1++;
						count++;
					}
					else if (board_info[j + count][i + count] == 0) {
						blank++;
						count++;
					}
					else {
						o1++;
						count++;
					}
				}

				count = 1;
				while ((j - count >= 0) && (i - count >= 0) && count <= 4)
				{
					if (board_info[j - count][i - count] == player)  //Check se to nw
					{
						p1++;
						count++;
					}
					else if (board_info[j - count][i - count] == 0) {
						blank++;
						count++;
					}
					else {
						o1++;
						count++;
					}
				}
				if (p1 == 1 && blank >= 2) {
					score[1][i] += 5;
				}
				else if (p1 == 2 && blank >= 1) {
					score[1][i] += 300;
				}
				else if (p1 == 3 && blank >= 0) {
					score[1][i] += 10000;
				}

				blank = 0;
				p1 = 0;
				o1 = 0;
				count = 1;

				while (j + count >= 0 && j + count < HEIGHT && count <= 4)
				{
					if (board_info[j + count][i] == player)  //Check down
					{
						p1++;
						count++;
					}
					else if (board_info[j + count][i] == 0) {
						blank++;
						count++;
					}
					else {
						o1++;
						count++;
					}
				}

				count = 1;
				while (j - count >= 0 && j - count < HEIGHT && count <= 4)
				{
					if (board_info[j - count][i] == player)  //Check up
					{
						p1++;
						count++;
					}
					else if (board_info[j - count][i] == 0) {
						blank++;
						count++;
					}
					else {
						o1++;
						count++;
					}
				}

				if (p1 == 1 && blank >= 2) {
					score[1][i] += 5;
				}
				else if (p1 == 2 && blank >= 1) {
					score[1][i] += 300;
				}
				else if (p1 == 3 && blank >= 0) {
					score[1][i] += 10000;
				}

				blank = 0;
				p1 = 0;
				o1 = 0;
				count = 1;

				while ((i + count >= 0) && (i + count < WIDTH) && count <= 4)
				{
					if (board_info[j][i + count] == player)  //Check left
					{
						p1++;
						count++;
					}
					else if (board_info[j][i + count] == 0) {
						blank++;
						count++;
					}
					else {
						o1++;
						count++;
					}
				}

				count = 1;
				while ((i - count >= 0) && (i - count < WIDTH) && count <= 4)
				{
					if (board_info[j][i - count] == player)  //Check right
					{
						p1++;
						count++;
					}
					else if (board_info[j][i - count] == 0) {
						blank++;
						count++;
					}
					else {
						o1++;
						count++;
					}
				}
				if (p1 == 1 && blank >= 2) {
					score[1][i] += 5;
				}
				else if (p1 == 2 && blank >= 1) {
					score[1][i] += 300;
				}
				else if (p1 == 3 && blank >= 0) {
					score[1][i] += 10000;
				}
			}
			else if (board_info[j][i] == 1 || board_info[j][i] == 2);
		}
	}
}
