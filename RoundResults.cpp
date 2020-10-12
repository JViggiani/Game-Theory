#include "RoundResults.hpp"

#include <string>
#include <exception>

RoundResults::RoundResults(const Decision& aDecisionPlayer1, const Decision& aDecisionPlayer2, const RewardConfig& aRewardConfig)
	: _player1Decision(aDecisionPlayer1),
	_player2Decision(aDecisionPlayer2)
{
	if(aDecisionPlayer1 == Decision::Cooperate && aDecisionPlayer2 == Decision::Cooperate)
	{
		_player1Reward = aRewardConfig._bothCooperate;
		_player2Reward = aRewardConfig._bothCooperate;
	}
	else if(aDecisionPlayer1 == Decision::Cheat && aDecisionPlayer2 == Decision::Cheat)
	{
		_player1Reward = aRewardConfig._bothCheat;
		_player2Reward = aRewardConfig._bothCheat;
	}
	else if(aDecisionPlayer1 == Decision::Cooperate && aDecisionPlayer2 == Decision::Cheat)
	{
		_player1Reward = aRewardConfig._cooperate;
		_player2Reward = aRewardConfig._cheat;
	}
	else if(aDecisionPlayer1 == Decision::Cheat && aDecisionPlayer2 == Decision::Cooperate)
	{
		_player1Reward = aRewardConfig._cheat;
		_player2Reward = aRewardConfig._cooperate;
	}
	else
	{
		std::string message = "Error: Player " + (aDecisionPlayer1 == Decision::Unset ? std::string("1") : std::string("2")) + " did not have a decision set. Cannot calculate reward, game is forfiet.";
		throw std::exception(message.c_str());
	}
}
