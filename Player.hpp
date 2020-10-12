#pragma once

#include <memory>

#include "Personality.hpp"
#include "RoundResults.hpp"
#include "Decision.hpp"

enum class PlayerNumber
{
	Unset = 0,
	One = 1,
	Two = 2
};

class Player
{
public:
	Player(const Personality& aPersonalityPtr);
	~Player() = default;
	//Player(const Player& aPlayer);

	void update(const RoundResults& results, const PlayerNumber& aPlayerNumber);

	Decision makeDecision();

	int getReward() const;

private:
	std::unique_ptr<Personality> _personality;
	int _reward;
	//Decision _lastOpponentMove;
		//JOSH perhaps a list of last moves?
};

