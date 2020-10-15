#pragma once

#include "eDecisionType.hpp"
#include "RewardConfig.hpp"

namespace Data
{

	struct RoundResults
	{
	public:
		RoundResults(const eDecisionType& aDecision1, const eDecisionType& aDecision2, const Config::RewardConfig& aRewardConfig);

		eDecisionType _player1Decision;
		eDecisionType _player2Decision;

		int _player1Reward;
		int _player2Reward;
	};

}