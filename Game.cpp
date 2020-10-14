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

	/*
	Game::~Game()
	{
		//JOSH do we want to reset here? Not if we want to reuse the players right?
		//_player1.reset();
		//_player2.reset();
	}
	*/

	GameResults Game::run()
	{
		BOOST_LOG_TRIVIAL(info) << "Game begin.";
		
		GameResults aGameResults;

		for(int aRoundCount = 0; aRoundCount < _numOfRounds; ++aRoundCount)
		{
			Machine* aMachine = Machine::GetInstance();

			//Round results should give the players the information required to make the next decision
			RoundResults aRoundResults = aMachine->processRound(_player1, _player2, aGameResults);
			
			aGameResults.update(aRoundResults);
		}

		BOOST_LOG_TRIVIAL(info) << "Game finished. Player 1 reward: " << aGameResults.getPlayer1Reward() << ". Player 2 reward: " << aGameResults.getPlayer2Reward();

		return aGameResults;
	}
}