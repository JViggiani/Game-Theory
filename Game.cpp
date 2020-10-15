#include "Game.hpp"

#include "Machine.hpp"
#include "RoundResults.hpp"

#include <boost/log/trivial.hpp>

namespace Core
{
	Data::GameResults Game::run()
	{
		BOOST_LOG_TRIVIAL(info) << "Game begin.";
		
		Data::GameResults aGameResults;

		for(int aRoundCount = 0; aRoundCount < _numOfRounds; ++aRoundCount)
		{
			Machine* aMachine = Machine::GetInstance();

			//Round results should give the players the information required to make the next decision
			Data::RoundResults aRoundResults = aMachine->processRound(_player1, _player2, aGameResults);
			
			aGameResults.update(aRoundResults);
		}

		BOOST_LOG_TRIVIAL(info) << "Game finished. Player 1 reward: " << aGameResults.getPlayer1Reward() << ". Player 2 reward: " << aGameResults.getPlayer2Reward();

		return aGameResults;
	}
}