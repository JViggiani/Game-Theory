#pragma once

#include "Decision.hpp"
#include "RewardConfig.hpp"

class RoundResults
{
public:
	RoundResults(const Decision& aDecision1, const Decision& aDecision2, const RewardConfig& aRewardConfig);

	Decision getPlayer1Decision() const;
	Decision getPlayer2Decision() const;
	int getPlayer1Reward() const;
	int getPlayer2Reward() const;
private:
	Decision _player1Decision;
	Decision _player2Decision;

	int _player1Reward;
	int _player2Reward;
};

