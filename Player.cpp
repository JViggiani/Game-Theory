#include "Player.hpp"

#include <string>
#include <exception>

namespace Core
{
	/*
	Player::Player(const Implementation::Personality& aPersonality)
	{
		_personality = aPersonality.clone();
	}
	*/
	Player::Player(const Data::ePersonalityType& aPersonality)
	{
		switch(aPersonality)
		{
		case Data::ePersonalityType::Cheater:
			_personality = std::make_unique<Implementation::PersonalityCheater>();
			break;
		case Data::ePersonalityType::Cooperator:
			_personality = std::make_unique<Implementation::PersonalityCooperator>();
			break;
		case Data::ePersonalityType::Copycat:
			_personality = std::make_unique<Implementation::PersonalityCopycat>();
			break;
		default:
			throw std::exception("Trying to construct an Unset Personality");
		}		
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