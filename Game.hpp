#pragma once

#include <memory>

#include "Player.hpp"
#include "RoundResults.hpp"

namespace Core
{
	///
	/// This class will manage game data and game loop.
	///
	class Game
	{
	public:
		///
		/// Main constructor.
		///
		explicit Game(const std::shared_ptr<Player>& player1, const std::shared_ptr<Player>& player2, const int& aNumberOfRounds)
			: _player1(player1),
			_player2(player2),
			_numOfRounds(aNumberOfRounds)
		{ };

		///
		/// Default destructor.
		///
		~Game();

		///
		/// Run the game loop.
		///
		void run();

	private:

		///
		/// Process game data.
		///
		/// \param results The results from the previous round.
		///
		void update(RoundResults results);

	
	private:

		std::shared_ptr<Player> _player1;
		std::shared_ptr<Player> _player2;

		int _numOfRounds;

	};
}

