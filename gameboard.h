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

	bool has_winning_lines() const
	{
		int score = calc_score();
		return (score == std::numeric_limits<int>::max() || score == std::numeric_limits<int>::min());
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

	int remove_stone(int col)
	{
		for (int row = ROW - 1; row >= 0; --row)
		{
			if (_board[row][col - 1] != 0)
			{
				_board[row][col - 1] = 0;
				--_moves;
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

	// heuristic
	int calc_score() const
	{
		int score = 0;

		// horizontal lines
		for (int row = 0; row < ROW; ++row)
		{
			for (int col = 0; col < COL - 3; ++col)
			{
				int horizontal_score = calc_score(row, col, 1, 0);
				if (horizontal_score == std::numeric_limits<int>::max() ||
					horizontal_score == std::numeric_limits<int>::min())
					return horizontal_score;

				score += horizontal_score;
			}
		}
		
		// vertical lines
		for (int row = 0; row < ROW - 3; ++row)
		{
			for (int col = 0; col < COL; ++col)
			{
				int vertical_score = calc_score(row, col, 0, 1);
				if (vertical_score == std::numeric_limits<int>::max() ||
					vertical_score == std::numeric_limits<int>::min())
					return vertical_score;

				score += vertical_score;
			}
		}

		// diagonal to right-top
		for (int row = 0; row < ROW - 3; ++row)
		{
			for (int col = 0; col < COL - 3; ++col)
			{
				int diagonal_score = calc_score(row, col, 1, 1);
				if (diagonal_score == std::numeric_limits<int>::max() ||
					diagonal_score == std::numeric_limits<int>::min())
					return diagonal_score;

				score += diagonal_score;
			}
		}

		// diagonal to left-top
		for (int row = 0; row < ROW - 3; ++row)
		{
			for (int col = 3; col < COL; ++col)
			{
				int diagonal_score = calc_score(row, col, -1, 1);
				if (diagonal_score == std::numeric_limits<int>::max() ||
					diagonal_score == std::numeric_limits<int>::min())
					return diagonal_score;

				score += diagonal_score;
			}
		}

		return score;
	}

private:
	// 6 rows, 7 cols
	// row 0 is the bottom-most row (stone gets piled up from row 0)
	char _board[ROW][COL];
	int _moves;

	int calc_score(int row, int col, int dx, int dy) const
	{
		int my_score = 0;
		int opponent_score = 0;

		for (int i = 0; i < 4; ++i)
		{
			// my stones
			if (_board[row][col] == 1)
				my_score++;
			else if (_board[row][col] == -1)
				opponent_score++;

			row += dy;
			col += dx;
		}

		if (my_score == 4)
			return std::numeric_limits<int>::max();
		else if (opponent_score == 4)
			return std::numeric_limits<int>::min();
		else
			return my_score;
	}
};
