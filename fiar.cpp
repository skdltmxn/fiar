#include "fiar.h"
#include "webrequest.h"
#include <algorithm>
#include <array>
#include <functional>
#include <sstream>
#include <string>
#include <vector>

void fiar::start()
{
    // initialize gameboard
    _gameboard.init();
    _playing = true;
	_turn = 0;
	_result = GAME_RESULT::DRAW;
	_seq = "";

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

    int row = _gameboard.add_stone(_myturn, col);
	if (_myturn)
		std::cout << "Putting stone at (" << row << ", " << col << ")" << std::endl;

    _turn++;
	_seq += std::to_string(col);
    _gameboard.draw_board();
    if (_gameboard.has_winning_lines())
    {
		_result = _myturn ? GAME_RESULT::WIN : GAME_RESULT::LOSE;
        _playing = false;
        return;
    }

	if (_gameboard.is_full())
	{
		_result = GAME_RESULT::DRAW;
		_playing = false;
		return;
	}

    _myturn = !_myturn;
}

void fiar::think()
{
    if (!is_playing()) return;

    std::cout << "Choose algorithm (1. heuristic / 2. rule) => ";
    int c;
    std::cin >> c;

    int col;
    switch (c)
    {
    default:
    case 1:
        // use heuristic
        col = think_heuristic();
        break;

    case 2:
        // use rule
        col = think_rule();
        break;
    }

	if (col == -1)
		return;

    put_stone(col);
}

// think using heuristic
// we use minmax algorithm and alpha-beta pruning
int fiar::think_heuristic()
{
	// first stone must not be placed in the center
	if (_turn == 0)
		return 3;

	int alpha = std::numeric_limits<int>::min();
	int beta = std::numeric_limits<int>::max();
	int col = 1;
	maximize(10, alpha, beta, col);

	for (; col < COL && !_gameboard.is_available(col); ++col);

	return col;
}

int fiar::maximize(int depth, int alpha, int beta, int &choice)
{
	int score = _gameboard.calc_score();

	if (score == std::numeric_limits<int>::max() ||
		score == std::numeric_limits<int>::min() ||
		!depth ||
		_gameboard.is_full())
		return score;

	std::vector<int> values(COL);

	for (int col = 1; col <= COL; ++col)
	{
		values[col - 1] = std::numeric_limits<int>::min();

		if (!_gameboard.is_available(col))
			continue;
		
		_gameboard.add_stone(true, col);		
		int m_value = minimize(depth - 1, alpha, beta, choice);
		_gameboard.remove_stone(col);

		if (m_value > values[col - 1])
			values[col - 1] = m_value;

		alpha = max(alpha, m_value);
		if (alpha >= beta)
			break;
	}

	choice = static_cast<int>(std::distance(values.begin(), std::max_element(values.begin(), values.end()))) + 1;
	return alpha;
}

int fiar::minimize(int depth, int alpha, int beta, int &choice)
{
	int score = _gameboard.calc_score();

	if (score == std::numeric_limits<int>::max() ||
		score == std::numeric_limits<int>::min() ||
		!depth ||
		_gameboard.is_full())
		return score;

	int value = std::numeric_limits<int>::max();
	for (int col = 1; col <= COL; ++col)
	{
		if (!_gameboard.is_available(col))
			continue;

		_gameboard.add_stone(false, col);
		int m_value = maximize(depth - 1, alpha, beta, choice);
		_gameboard.remove_stone(col);

		if (m_value < value)
			value = m_value;

		beta = min(beta, m_value);
		if (alpha >= beta)
			break;
	}

	return beta;
}

int fiar::think_rule()
{
	// Rule1: first move is deterministic
	if (!_turn)
	{
		std::cout << "Rule: (1, 3) on first move" << std::endl;
		return 3;
	}

	auto web = web_request("connect4.gamesolver.org", 80);
	auto res = web.get("/solve", "pos", _seq);

	// {"pos":"XXX","score":[2,2,1,-1,4,1,3]}
	auto pos = res.find("score\":[") + 8;
	auto array = res.substr(pos, res.find("]}") - pos);
	std::istringstream is(array);
	std::string score_str;
	std::array<std::pair<int, int>, COL> scores; // pair<score, col>
	int i = 0;

	while (std::getline(is, score_str, ','))
	{
		int score = std::strtol(score_str.c_str(), nullptr, 10);
		if (score == 100)
			score = std::numeric_limits<int>::min();

		scores[i++] = std::make_pair(score, i);
	}

	std::sort(scores.begin(), scores.end(), std::greater<decltype(scores[0])>());

	// cols with highes score
	std::vector<int> possible;

	for (auto score : scores)
	{
		if (score.first == scores[0].first)
			possible.push_back(score.second);
	}

	// Rule2: there is only one best move
	if (possible.size() == 1)
	{
		std::cout << "Rule: Single best move found with score " << scores[0].first << std::endl;
		return possible[0];
	}

	// Rule3: multiple best moves
	int max_score = std::numeric_limits<int>::min();
	int max_col = 1;
	for (auto col : possible)
	{
		_gameboard.add_stone(true, col);
		int score = _gameboard.calc_score();
		if (score > max_score)
		{
			max_score = score;
			max_col = col;
		}
		_gameboard.remove_stone(col);
	}
	std::cout << "Rule: Best board score when multiple possible moves found, score: " << max_score << std::endl;

    return max_col;
}
