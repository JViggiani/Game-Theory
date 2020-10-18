#include "Player.hpp"

#include <string>
#include <exception>

namespace Core
{
	unsigned int Player::_idCounter;
	
	/*
	Player::Player(const Implementation::Personality& aPersonality)
	{
		_personality = aPersonality.clone();
	}
	*/
	Player::Player(const Data::ePersonalityType& aPersonality)
	{
		_id = _idCounter;
		_idCounter++;
		_personalityType = aPersonality;
		// Reward can go negative but should start at 0
		_cumulativeReward = 0;

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
		_personalityType = aPlayer._personalityType;
		_id = _idCounter;
		_idCounter++;
		_cumulativeReward = aPlayer._cumulativeReward;
	}

	Player& Player::operator=(const Player& aPlayer)
	{
		_personality = aPlayer._personality->clone();
		_personalityType = aPlayer._personalityType;
		_id = _idCounter;
		_idCounter++;
		_cumulativeReward = aPlayer._cumulativeReward;
		return *this;
	}

	Player& Player::operator=(const Player&& aPlayer) noexcept
	{
		_personality = aPlayer._personality->clone();
		_personalityType = aPlayer._personalityType;
		_id = _idCounter;
		_idCounter++;
		_cumulativeReward = aPlayer._cumulativeReward;
		return *this;
	}

	Data::eDecisionType Player::makeDecision(const Data::GameResults& aDecisionData, const Data::ePlayerNumber& aPlayerNumber)
	{
		return _personality->makeDecision(aDecisionData, aPlayerNumber);
	}

	void Player::updateGameReward(const Data::GameResults& aGameResults, const Data::ePlayerNumber& aPlayerNumber)
	{
		if(aPlayerNumber == Data::ePlayerNumber::One)
		{
			this->_cumulativeReward += aGameResults.getPlayer1Reward();
		}
		else if(aPlayerNumber == Data::ePlayerNumber::Two)
		{
			this->_cumulativeReward += aGameResults.getPlayer2Reward();
		}
		else
		{
			throw std::exception("Player number was not set in Player::updateGameRewards. Could not update game rewards!");
		}
	}

	void Player::resetGameReward()
	{
		_cumulativeReward = 0;
	}

}