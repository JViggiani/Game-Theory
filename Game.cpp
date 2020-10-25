#include "Game.hpp"

#include "Machine.hpp"
#include "RoundResults.hpp"

#include <boost/log/trivial.hpp>

namespace Core
{
	Data::GameResults Game::run()
	{
		BOOST_LOG_TRIVIAL(debug) << "Running game."; 
		BOOST_LOG_TRIVIAL(debug) << "Player 1 ID: " << _player1->getId();
		BOOST_LOG_TRIVIAL(trace) << "Player 1 Personality: " << std::to_string(static_cast<int>(_player1->getPersonalityType()));
		BOOST_LOG_TRIVIAL(debug) << "Player 2 ID: " << _player2->getId();
		BOOST_LOG_TRIVIAL(trace) << "Player 2 Personality: " << std::to_string(static_cast<int>(_player2->getPersonalityType()));

		if(_player1->getId() == _player2->getId())
		{
			throw std::exception("Comparing the same players to each other. Cannot run game.");
		}

		Data::GameResults aGameResults;

		for(int aRoundCount = 0; aRoundCount < _numOfRounds; ++aRoundCount)
		{
			Machine* aMachine = Machine::GetInstance();

			//Round results should give the players the information required to make the next decision
			Data::RoundResults aRoundResults = aMachine->processRound(_player1, _player2, aGameResults);
			
			aGameResults.update(aRoundResults);
		}

		BOOST_LOG_TRIVIAL(debug) << "Updating Players with rewards.";

		_player1->updateGameReward(aGameResults, Data::ePlayerNumber::One);
		_player2->updateGameReward(aGameResults, Data::ePlayerNumber::Two);

		BOOST_LOG_TRIVIAL(debug) << "Game finished.";

		return aGameResults;
	}
}