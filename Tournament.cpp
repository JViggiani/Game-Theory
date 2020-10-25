#include "Tournament.hpp"
#include "Game.hpp"

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

namespace Core
{
	Tournament::Tournament(const Config::TournamentConfig& aTournamentConfig)
	{
        BOOST_LOG_TRIVIAL(debug) << "Constructing Tournament";
        
        //JOSH consider just storing the config as an attribute directly. Though we would have player config.. maybe worth separating them?
        _numOfEvolutions = aTournamentConfig._numOfEvolutions;
        _numOfRounds = aTournamentConfig._numOfRounds;
        _numOfEliminationEvolutions = aTournamentConfig._numOfEliminationEvolutions;

        //Populate Players
        for(int i = 0; i < aTournamentConfig._numCheaters; ++i)
        {
            _players.push_back(std::make_shared<Core::Player>(Core::Player(Data::ePersonalityType::Cheater)));
        }
        for(int i = 0; i < aTournamentConfig._numCooperators; ++i)
        {
            _players.push_back(std::make_shared<Core::Player>(Core::Player(Data::ePersonalityType::Cooperator)));
        }
        for(int i = 0; i < aTournamentConfig._numCopycats; ++i)
        {
            _players.push_back(std::make_shared<Core::Player>(Core::Player(Data::ePersonalityType::Copycat)));
        }
        for(int i = 0; i < aTournamentConfig._numVengeful; ++i)
        {
            _players.push_back(std::make_shared<Core::Player>(Core::Player(Data::ePersonalityType::Vengeful)));
        }
        for(int i = 0; i < aTournamentConfig._numCopykitten; ++i)
        {
            _players.push_back(std::make_shared<Core::Player>(Core::Player(Data::ePersonalityType::Copykitten)));
        }
        for(int i = 0; i < aTournamentConfig._numMeanCopycat; ++i)
        {
            _players.push_back(std::make_shared<Core::Player>(Core::Player(Data::ePersonalityType::MeanCopycat)));
        }
        for(int i = 0; i < aTournamentConfig._numRandom; ++i)
        {
            _players.push_back(std::make_shared<Core::Player>(Core::Player(Data::ePersonalityType::Random)));
        }
        for(int i = 0; i < aTournamentConfig._numWinStayLoseSwitch; ++i)
        {
            _players.push_back(std::make_shared<Core::Player>(Core::Player(Data::ePersonalityType::WinStayLoseSwitch)));
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
