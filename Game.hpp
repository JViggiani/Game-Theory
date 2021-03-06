#pragma once

#include <memory>

#include "Player.hpp"
#include "RoundResults.hpp"

namespace Core
{
	//! This class will manage game data and game loop.
	class Game
	{
	public:

		///	Constructors and Destructors ///

		//! Main constructor.
		explicit Game(const std::shared_ptr<Player>& player1, const std::shared_ptr<Player>& player2, const int& aNumberOfRounds)
			: _player1(player1),
			_player2(player2),
			_numOfRounds(aNumberOfRounds)
		{ };

		//! Default destructor.
		~Game() = default;

		//! Default copy constructor
		Game(const Game&) = default;

		//! Default move constructor
		Game(Game&&) = default;

		///	Operators ///

		//! Default copy assignment
		Game& operator=(const Game&) = default;

		//! Default move assignment
		Game& operator=(Game&&);

		///	Functions ///

		//! Run the game loop.
		Data::GameResults run();

	private:

		std::shared_ptr<Player> _player1;
		std::shared_ptr<Player> _player2;

		int _numOfRounds;
	};
}

