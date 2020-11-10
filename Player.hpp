#pragma once

#include <memory>
#include <string>
#include <typeinfo>

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
	protected:
		//! Main constructor.
		/*
			Use the static templated create function
		*/
		Player();
	
	public:
		/// Constructors and Destructors ///

		template <typename T> 
		static Player create()
		{
			Player aPlayer;
			aPlayer._personality = std::make_unique<T>();

			return aPlayer;
		};

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
		/*
			aMistakeChance is a int between 0 and 100
		*/
		Data::eDecisionType makeDecision(const Data::GameResults& aDecisionData, const Data::ePlayerNumber& aPlayerNumber, unsigned int aMistakeChance);

		int getId() const
		{
			return _id;
		}

		Data::ePersonalityType getPersonalityType() const
		{
			return _personality->getPersonalityType();
		}

		int getCumulativeReward() const
		{
			return _cumulativeReward;
		}

		void updateGameReward(const Data::GameResults& aGameResults, const Data::ePlayerNumber& aPlayerNumber);

		void resetGameReward();

	private:

		/*
			This Personality makes the important decisions. It does not hold any data.

			This must be a pointer because Personality is abstract
			We want to be able to polymorphically use the correct personality child here
			Perhaps C++23 will have polymorphic_value<T> :(
		*/
		std::unique_ptr<Implementation::Personality> _personality;

		unsigned int _id;
		unsigned static int _idCounter;
		int _cumulativeReward;
	};
}