#pragma once

#include "RoundResults.hpp"

#include <vector>

namespace Data
{

	//! Tracks the decisions made by players in a Game and the rewards they achieved
	class GameResults
	{
	public:
		/// Constructors and Destructors ///

		//! Main constructor.
		GameResults() = default;

		//! Default destructor.
		~GameResults() = default;

		//! Default copy constructor
		GameResults(const GameResults&) = default;

		//! Default move constructor
		GameResults(GameResults&&) = default;

		/// Operators ///

		//! Default copy assignment
		GameResults& operator=(const GameResults&) = default;

		//! Default move assignment
		GameResults& operator=(GameResults&&);

		/// Functions ///

		std::vector<eDecisionType> const& getPlayer1Decisions() const
		{
			return _player1Decisions;
		}
		std::vector<eDecisionType> const& getPlayer2Decisions() const
		{
			return _player2Decisions;
		}

		const std::vector<int>& getPlayer1Reward() const
		{
			return _player1Rewards;
		}
		const std::vector<int>& getPlayer2Reward() const
		{
			return _player2Rewards;
		}

		//Moves the data from the given RoundResults object into the game results.
		//	Do not use the RoundResults object after calling this function
		void update(RoundResults& aRoundResults);

	private:
		std::vector<eDecisionType> _player1Decisions;
		std::vector<eDecisionType> _player2Decisions;

		std::vector<int> _player1Rewards;
		std::vector<int> _player2Rewards;
	};

}