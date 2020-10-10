#pragma once

#include "Personality.hpp"
#include "RoundResults.hpp"

class Player
{
public:
	Player() = default;

	~Player() = default;

	void update(RoundResults results);

private:
	Personality _personality;
};

