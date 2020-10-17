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
	Player::Player(const Data::ePersonalityType& aPersonality, const int& aId)
	{
		_id = aId;
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

	/*
	std::string Player::getPersonalityTypeStr() const
	{
		switch(_personalityType)
		{
		case Data::ePersonalityType::Cheater:
			return "CHEATER";
		case Data::ePersonalityType::Cooperator:
			return "COOPERATOR";
		case Data::ePersonalityType::Copycat:
			return "COPYCAT";
		default:
			throw std::exception("Could not determine personality type. Did you forget to declare it in ePersonalityType?");
		}
	}
	*/

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