#pragma once

#include "Decision.hpp"
#include "RewardConfig.hpp"

namespace Data
{

	struct RoundResults
	{
	public:
		RoundResults(const Decision& aDecision1, const Decision& aDecision2, const Config::RewardConfig& aRewardConfig);

		Decision _player1Decision;
		Decision _player2Decision;

		int _player1Reward;
		int _player2Reward;
	};

}