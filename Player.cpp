#include "Player.hpp"

#include <string>
#include <exception>

//JOSH should refactor to not accept raw ptrs.. generate a unique ptr early 
Player::Player(const Personality& aPersonality)
{
	_personality = aPersonality.clone();
}

Decision Player::makeDecision(const GameResults& aDecisionData, const PlayerNumber& aPlayerNumber)
{
	//JOSH implement me
	return _personality->makeDecision(aDecisionData, aPlayerNumber);
}