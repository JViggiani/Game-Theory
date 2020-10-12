#include "GameResults.hpp"

GameResults::GameResults()
{
	_player1Reward = 0;
	_player2Reward = 0;
}

void GameResults::update(const RoundResults& aRoundResults)
{
	_player1Decisions.push_back(aRoundResults._player1Decision);
	_player2Decisions.push_back(aRoundResults._player2Decision);

	_player1Reward += aRoundResults._player1Reward;
	_player2Reward += aRoundResults._player2Reward;
}
