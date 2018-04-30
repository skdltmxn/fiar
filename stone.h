#pragma once

class stone
{
public:
	explicit stone(bool mine) : _mine(mine) {}
	bool is_mine() const { return _mine; }
	char symbol() const { return _mine ? 'O' : 'X'; }

private:
	bool _mine;
};
