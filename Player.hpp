#pragma once

#include <memory>

#include "Personality.hpp"
#include "RoundResults.hpp"
#include "Decision.hpp"
#include "PlayerNumber.hpp"

//! This class is a wrapper around the polymorphic Personality pointer. Decisions should be delegated to the Personality.
class Player
{
public:
	/// Constructors and Destructors ///

	//! Main constructor.
	Player(const Personality& aPersonality);

	//! Default destructor.
	~Player() = default;

	//! Copy constructor
	Player(const Player& aPlayer);

	//! Default move constructor
	Player(Player&&) = default;

	/// Operators ///

	//! Default copy assignment
	Player& operator=(const Player& aPlayer);

	//! Default move assignment
	Player& operator=(const Player&& aPlayer) noexcept;

	/// Functions ///

	//Calls the polymorphic Personality makeDecision() function
	Decision makeDecision(const GameResults& aDecisionData, const PlayerNumber& aPlayerNumber);

private:
	/*
		This must be a pointer because Personality is abstract
		We want to be able to polymorphically use the correct personality child here
		Perhaps C++23 will have polymorphic_value<T> :( 
	*/
	std::unique_ptr<Personality> _personality;
};

