#include "Game.hpp"

#include "Machine.hpp"
#include "RoundResults.hpp"

namespace Core
{
	Game::Game(std::shared_ptr<Player> player1, std::shared_ptr<Player> player2)
	{
		_player1 = player1;
		_player2 = player2;
	}

	void Game::run()
	{		
		for(int aRoundCount = 0; aRoundCount < _numOfRounds; ++aRoundCount)
		{
			//call game event at the begin
			// ..
			//call game update() at the end
		}

		_player1.reset();
		_player2.reset();
	}

	void Game::event()
	{
		// JOSH todo
		// Process game events
		while(false) // while event
		{
			// Process system events.
			Machine* machine = Machine::GetInstance();
			machine->processEvent(_player1, _player2);
		}
	}

	void Game::update(RoundResults results)
	{
		_player1->update(results);
		_player2->update(results);
	}
}