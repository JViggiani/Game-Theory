#include "Game.hpp"

#include "Machine.hpp"
#include "RoundResults.hpp"

#include <boost/log/trivial.hpp>

namespace Core
{
	/*
	Game::Game(std::shared_ptr<Player> player1, std::shared_ptr<Player> player2, int aNumberOfRounds)
	{
		_player1 = player1;
		_player2 = player2;

		_numOfRounds = aNumberOfRounds;
	}
	*/

	Game::~Game()
	{
		_player1.reset();
		_player2.reset();
	}

	void Game::run()
	{
		BOOST_LOG_TRIVIAL(info) << "Game begin.";
		
		for(int aRoundCount = 0; aRoundCount < _numOfRounds; ++aRoundCount)
		{
			Machine* aMachine = Machine::GetInstance();

			//Round results should give the players the information required to make the next decision
			RoundResults aRoundResults = aMachine->processRound(_player1, _player2);
			
			this->update(aRoundResults);
		}

		BOOST_LOG_TRIVIAL(info) << "Game finished. Player 1 reward: " << _player1->getReward() << ". Player 2 reward: " << _player2->getReward();
	}

	void Game::update(const RoundResults& results)
	{
		_player1->update(results, PlayerNumber::One);
		_player2->update(results, PlayerNumber::Two);
	}
}