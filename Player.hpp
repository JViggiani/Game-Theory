#pragma once

#include <memory>

#include "Personality.hpp"
#include "RoundResults.hpp"
#include "Decision.hpp"

class Player
{
public:
	Player(const Personality& aPersonalityPtr);
	~Player() = default;
	//Player(const Player& aPlayer);

	void update(const RoundResults& results);

	Decision makeDecision();

private:
	std::unique_ptr<Personality> _personality;
	//Decision _lastOpponentMove;
		//JOSH perhaps a list of last moves?
};

