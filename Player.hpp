#pragma once

#include <memory>

#include "Personality.hpp"
#include "RoundResults.hpp"
#include "Decision.hpp"
#include "PlayerNumber.hpp"

class Player
{
public:
	Player(const Personality& aPersonalityPtr);
	~Player() = default;
	//Player(const Player& aPlayer);

	Decision makeDecision(const GameResults& aDecisionData, const PlayerNumber& aPlayerNumber);

private:
	std::unique_ptr<Personality> _personality;
};

