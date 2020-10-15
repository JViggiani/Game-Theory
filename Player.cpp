#include "Player.hpp"

#include <string>
#include <exception>

namespace Core
{

	Player::Player(const Implementation::Personality& aPersonality)
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

	Data::eDecisionType Player::makeDecision(const Data::GameResults& aDecisionData, const Data::ePlayerNumber& aPlayerNumber)
	{
		return _personality->makeDecision(aDecisionData, aPlayerNumber);
	}

}