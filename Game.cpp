#include "Game.hpp"

#include "Machine.hpp"
#include "RoundResults.hpp"

#include <boost/log/trivial.hpp>

namespace Core
{
	Data::GameResults Game::run()
	{
		BOOST_LOG_TRIVIAL(info) << "Running game."; 
		BOOST_LOG_TRIVIAL(info) << "Player 1 ID: " << _player1->getId();
		BOOST_LOG_TRIVIAL(debug) << "Player 1 Personality: " << _player1->getPersonalityTypeStr();
		BOOST_LOG_TRIVIAL(info) << "Player 2 ID: " << _player2->getId();
		BOOST_LOG_TRIVIAL(debug) << "Player 2 Personality: " << _player2->getPersonalityTypeStr();

		Data::GameResults aGameResults;

		for(int aRoundCount = 0; aRoundCount < _numOfRounds; ++aRoundCount)
		{
			Machine* aMachine = Machine::GetInstance();

			//Round results should give the players the information required to make the next decision
			Data::RoundResults aRoundResults = aMachine->processRound(_player1, _player2, aGameResults);
			
			aGameResults.update(aRoundResults);
		}

		BOOST_LOG_TRIVIAL(debug) << "Player 1 reward: " << aGameResults.getPlayer1Reward();
		BOOST_LOG_TRIVIAL(debug) << "Player 2 reward: " << aGameResults.getPlayer2Reward();
		BOOST_LOG_TRIVIAL(info) << "Game finished.";

		return aGameResults;
	}
}