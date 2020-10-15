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
		GameResults();

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

		std::vector<Decision> const& getPlayer1Decisions() const
		{
			return _player1Decisions;
		}
		std::vector<Decision> const& getPlayer2Decisions() const
		{
			return _player2Decisions;
		}

		int getPlayer1Reward() const
		{
			return _player1Reward;
		}
		int getPlayer2Reward() const
		{
			return _player2Reward;
		}

		void update(const RoundResults& aRoundResults);

	private:
		std::vector<Decision> _player1Decisions;
		std::vector<Decision> _player2Decisions;

		int _player1Reward;
		int _player2Reward;
	};

}