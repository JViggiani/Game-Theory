#include "Player.hpp"

#include <string>
#include <exception>

//JOSH should refactor to not accept raw ptrs.. generate a unique ptr early 
Player::Player(const Personality& aPersonality)
{
	_personality = aPersonality.clone();
	_reward = 0;
}

void Player::update(const RoundResults& results, const PlayerNumber& aPlayerNumber)
{
	//JOSH implement me
	if(aPlayerNumber == PlayerNumber::One)
	{
		_reward += results.getPlayer1Reward();
	}
	else if(aPlayerNumber == PlayerNumber::Two)
	{
		_reward += results.getPlayer2Reward();
	}
	else
	{
		std::string message = "Error: Player number was not set. Cannot update reward, game is forfiet.";
		throw std::exception(message.c_str());
	}
}

Decision Player::makeDecision()
{
	//JOSH implement me
	return _personality->makeDecision();
}

int Player::getReward() const
{
	return _reward;
}
