#pragma once

#include <memory>

#include "Personality.hpp"
#include "RoundResults.hpp"
#include "eDecisionType.hpp"
#include "ePlayerNumber.hpp"
#include "ePersonalityType.hpp"

namespace Core
{

	//! This class is a wrapper Proxy around the polymorphic Personality pointer. Decisions should be delegated to the Personality.
	class Player
	{
	public:
		/// Constructors and Destructors ///

		//! Main constructor.
		//Player(const Implementation::Personality& aPersonality);
		Player(const Data::ePersonalityType& aPersonality);

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
		Data::eDecisionType makeDecision(const Data::GameResults& aDecisionData, const Data::ePlayerNumber& aPlayerNumber);

	private:
		/*
			This must be a pointer because Personality is abstract
			We want to be able to polymorphically use the correct personality child here
			Perhaps C++23 will have polymorphic_value<T> :(
		*/
		std::unique_ptr<Implementation::Personality> _personality;
	};

}