#include "Player.hpp"

#include <string>
#include <exception>

Player::Player(const Personality& aPersonality)
{
	_personality = aPersonality.clone();
}

Player::Player(const Player& aPlayer)
{
	_personality = aPlayer._personality->clone();
}

Player& Player::operator=(const Player& aPlayer)
{
	this->_personality = aPlayer._personality->clone();
	return *this;
}

Player& Player::operator=(const Player&& aPlayer) noexcept
{
	this->_personality = aPlayer._personality->clone();
	return *this;
}

Decision Player::makeDecision(const GameResults& aDecisionData, const PlayerNumber& aPlayerNumber)
{
	return _personality->makeDecision(aDecisionData, aPlayerNumber);
}


