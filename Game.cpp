#include "Game.hpp"

#include "Machine.hpp"
#include "RoundResults.hpp"

#include <boost/log/trivial.hpp>

namespace Core
{
	Game::Game(std::shared_ptr<Player> player1, std::shared_ptr<Player> player2, int aNumberOfRounds)
	{
		_player1 = player1;
		_player2 = player2;

		_numOfRounds = aNumberOfRounds;
	}

	Game::~Game()
	{
		_player1.reset();
		_player2.reset();
	}

	void Game::run()
	{
		for(int aRoundCount = 0; aRoundCount < _numOfRounds; ++aRoundCount)
		{
			BOOST_LOG_TRIVIAL(info) << "Iterating game";

			Machine* aMachine = Machine::GetInstance();

			//Round results should give the players the information required to make the next decision
			RoundResults aRoundResults = aMachine->processRound(_player1, _player2);
			
			this->update(aRoundResults);
		}
	}

	void Game::update(RoundResults results)
	{
		_player1->update(results);
		_player2->update(results);
	}
}