#include "Player.hpp"

//JOSH should refactor to not accept raw ptrs.. generate a unique ptr early 
Player::Player(const Personality& aPersonality)
{
	_personality = aPersonality.clone();
}

void Player::update(const RoundResults& results)
{
	//JOSH implement me
}

Decision Player::makeDecision()
{
	//JOSH implement me
	return _personality->makeDecision();
}
