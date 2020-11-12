#include "Tournament.hpp"
#include "Game.hpp"
#include "Personality.hpp"

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

namespace Core
{
	Tournament::Tournament(const Config::TournamentConfig& aTournamentConfig)
        :
            _numOfEvolutions(aTournamentConfig._processConfig._numOfEvolutions),
            _numOfRounds(aTournamentConfig._processConfig._numOfRounds),
            _numOfEliminationEvolutions(aTournamentConfig._processConfig._numOfEliminationEvolutions)
	{
        BOOST_LOG_TRIVIAL(debug) << "Constructing Tournament";

        //Populate Players
        for(int i = 0; i < aTournamentConfig._playerConfig._numCheaters; ++i)
        {
            _players.push_back(std::make_shared<Core::Player>(Core::Player::create<Implementation::PersonalityCheater>()));
        }
        for(int i = 0; i < aTournamentConfig._playerConfig._numCooperators; ++i)
        {
            _players.push_back(std::make_shared<Core::Player>(Core::Player::create<Implementation::PersonalityCooperator>()));
        }
        for(int i = 0; i < aTournamentConfig._playerConfig._numCopycats; ++i)
        {
            _players.push_back(std::make_shared<Core::Player>(Core::Player::create<Implementation::PersonalityCopycat>()));
        }
        for(int i = 0; i < aTournamentConfig._playerConfig._numVengeful; ++i)
        {
            _players.push_back(std::make_shared<Core::Player>(Core::Player::create<Implementation::PersonalityVengeful>()));
        }
        for(int i = 0; i < aTournamentConfig._playerConfig._numCopykitten; ++i)
        {
            _players.push_back(std::make_shared<Core::Player>(Core::Player::create<Implementation::PersonalityCopykitten>()));
        }
        for(int i = 0; i < aTournamentConfig._playerConfig._numMeanCopycat; ++i)
        {
            _players.push_back(std::make_shared<Core::Player>(Core::Player::create<Implementation::PersonalityMeanCopycat>()));
        }
        for(int i = 0; i < aTournamentConfig._playerConfig._numRandom; ++i)
        {
            _players.push_back(std::make_shared<Core::Player>(Core::Player::create<Implementation::PersonalityRandom>()));
        }
        for(int i = 0; i < aTournamentConfig._playerConfig._numWinStayLoseSwitch; ++i)
        {
            _players.push_back(std::make_shared<Core::Player>(Core::Player::create<Implementation::PersonalityWinStayLoseSwitch>()));
        }
	}
	
    Data::TournamentResults Core::Tournament::run()
	{
        BOOST_LOG_TRIVIAL(debug) << "Beginning Tournament";
        
        for(int aEvolutionsIt = 0; aEvolutionsIt < _numOfEvolutions; ++aEvolutionsIt)
        {
            iterate();
            evolve();
        }

        BOOST_LOG_TRIVIAL(debug) << "Finishing Tournament";
        
        Data::TournamentResults aTournamentResults(this->_players);
        return aTournamentResults;
	}

    //Represents one iteration by comparing each player to every other player. 
    void Tournament::iterate()
    {
        for(auto aOuterPlayerIt = _players.begin(); aOuterPlayerIt != _players.end(); aOuterPlayerIt++)
        {
            for(auto aInnerPlayerIt = _players.begin(); aInnerPlayerIt != _players.end(); aInnerPlayerIt++)
            {
                if(aOuterPlayerIt == aInnerPlayerIt)
                {
                    continue;
                }

                Core::Game aGame(*aOuterPlayerIt, *aInnerPlayerIt, _numOfRounds);
                Data::GameResults aGameResults = aGame.run();
            }
        }
    }

    // Evolves the set of players. 
    /*
        Eliminates the lowest scoring n players and replicates the highest scoring n players.
        Cumulative player rewards reset afterwards.
    */
    void Tournament::evolve()
    {
		// First sort players
		std::sort(_players.begin(), _players.end(),
				  [](const std::shared_ptr<Core::Player>& a, const std::shared_ptr<Core::Player>& b)
		{
			return a->getCumulativeReward() > b->getCumulativeReward();
		});

		// Eliminate bottom players
		for(int aPlayerEliminateIt = 0; aPlayerEliminateIt < _numOfEliminationEvolutions; aPlayerEliminateIt++)
		{
			_players.pop_back();
		}

		// Evolve top players
		std::vector<std::shared_ptr<Core::Player> > aEvolvePlayers;
		std::transform(_players.begin(), _players.begin() + _numOfEliminationEvolutions, std::back_inserter(aEvolvePlayers),
					   [](const std::shared_ptr<Core::Player>& ptr) -> std::shared_ptr<Core::Player>
		{
			return std::make_shared<Core::Player>(*ptr);
		});
		_players.insert(_players.end(), std::make_move_iterator(aEvolvePlayers.begin()),
						std::make_move_iterator(aEvolvePlayers.end()));

		// Reset game rewards so there is no carry over into the next games
		resetGameRewards();
    }

    void Tournament::resetGameRewards()
    {
        for(auto aPlayer : _players)
        {
            aPlayer->resetGameReward();
        }
    }

}
