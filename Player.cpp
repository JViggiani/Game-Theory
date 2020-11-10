#include "Player.hpp"

#include <string>
#include <exception>
#include <numeric>

#include <boost/log/trivial.hpp>

namespace Core
{
	unsigned int Player::_idCounter;
	
	Player::Player()
	{
		_id = _idCounter;
		_idCounter++;
		// Reward can go negative but should start at 0
		_cumulativeReward = 0;	
	}

	Player::Player(const Player& aPlayer)
	{
		_personality = aPlayer._personality->clone();
		//_personalityType = aPlayer._personalityType;
		_id = _idCounter;
		_idCounter++;
		_cumulativeReward = aPlayer._cumulativeReward;
	}

	Player& Player::operator=(const Player& aPlayer)
	{
		_personality = aPlayer._personality->clone();
		//_personalityType = aPlayer._personalityType;
		_id = _idCounter;
		_idCounter++;
		_cumulativeReward = aPlayer._cumulativeReward;
		return *this;
	}

	Player& Player::operator=(const Player&& aPlayer) noexcept
	{
		_personality = aPlayer._personality->clone();
		//_personalityType = aPlayer._personalityType;
		_id = _idCounter;
		_idCounter++;
		_cumulativeReward = aPlayer._cumulativeReward;
		return *this;
	}

	Data::eDecisionType Player::makeDecision(const Data::GameResults& aDecisionData, const Data::ePlayerNumber& aPlayerNumber, unsigned int aMistakeChance)
	{
		return _personality->makeDecision(aDecisionData, aPlayerNumber, aMistakeChance);
	}

	void Player::updateGameReward(const Data::GameResults& aGameResults, const Data::ePlayerNumber& aPlayerNumber)
	{
		if(aPlayerNumber == Data::ePlayerNumber::One)
		{
			int aCumulativeReward = std::accumulate(aGameResults.getPlayer1Reward().begin(), aGameResults.getPlayer1Reward().end(), 0);
			
			BOOST_LOG_TRIVIAL(trace) << "Player 1 reward: " << aCumulativeReward;
			this->_cumulativeReward += aCumulativeReward;
		}
		else if(aPlayerNumber == Data::ePlayerNumber::Two)
		{
			int aCumulativeReward = std::accumulate(aGameResults.getPlayer2Reward().begin(), aGameResults.getPlayer2Reward().end(), 0);

			BOOST_LOG_TRIVIAL(trace) << "Player 2 reward: " << aCumulativeReward;
			this->_cumulativeReward += aCumulativeReward;
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