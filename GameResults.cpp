#include "GameResults.hpp"

namespace Data
{

	void GameResults::update(RoundResults& aRoundResults)
	{
		_player1Decisions.push_back(std::move(aRoundResults._player1Decision));
		_player2Decisions.push_back(std::move(aRoundResults._player2Decision));

		_player1Rewards.push_back(aRoundResults._player1Reward);
		_player2Rewards.push_back(aRoundResults._player2Reward);
	}

}