#pragma once

#include "RoundResults.hpp"

#include <vector>

struct GameResults
{
	GameResults();
	
	std::vector<Decision> _player1Decisions;
	std::vector<Decision> _player2Decisions;

	int _player1Reward;
	int _player2Reward;

	void update(const RoundResults& aRoundResults);
};

