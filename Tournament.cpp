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
        BOOST_LOG_TRIVIAL(info) << "Constructing Tournament";
        
        //JOSH consider just storing the config as an attribute directly. Though we would have player config.. maybe worth separating them?
        _numOfEvolutions = aTournamentConfig._numOfEvolutions;
        _numOfRounds = aTournamentConfig._numOfRounds;
        _numOfEliminationEvolutions = aTournamentConfig._numOfEliminationEvolutions;

        int aIdCount = 0;

        //Populate Players
        for(int i = 0; i < aTournamentConfig._numCheaters; ++i)
        {
            _players.push_back(std::make_shared<Core::Player>(Core::Player(Data::ePersonalityType::Cheater, aIdCount)));
            ++aIdCount;
        }
        for(int i = 0; i < aTournamentConfig._numCooperators; ++i)
        {
            _players.push_back(std::make_shared<Core::Player>(Core::Player(Data::ePersonalityType::Cooperator, aIdCount)));
            ++aIdCount;
        }
        for(int i = 0; i < aTournamentConfig._numCopycats; ++i)
        {
            _players.push_back(std::make_shared<Core::Player>(Core::Player(Data::ePersonalityType::Copycat, aIdCount)));
            ++aIdCount;
        }
	}
	
    Data::TournamentResults Core::Tournament::run()
	{
        BOOST_LOG_TRIVIAL(info) << "Beginning Tournament";
        
        for(int aEvolutionsIt = 0; aEvolutionsIt < _numOfEvolutions; ++aEvolutionsIt)
        {
            iterate();
            evolve();
        }

        BOOST_LOG_TRIVIAL(info) << "Finishing Tournament";
        
        Data::TournamentResults aTournamentResults(this->_players);
        return aTournamentResults;
	}

    //Represents one iteration by comparing each player to every other player. 
    void Tournament::iterate()
    {
        //JOSH fix this iteration. You should use container iterators.. 
        for(int aOuterPlayerIt = 0; aOuterPlayerIt < _players.size(); aOuterPlayerIt++)
        {
            for(int aInnerPlayerIt = 0; aInnerPlayerIt < _players.size() - 1; aInnerPlayerIt++)
            {
                if(aOuterPlayerIt == aInnerPlayerIt)
                {
                    continue;
                }

                Core::Game aGame(_players[aOuterPlayerIt], _players[aInnerPlayerIt], _numOfRounds);
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
        } );

        // Eliminate bottom players
        for(int aPlayerEliminateIt = 0; aPlayerEliminateIt < _numOfEliminationEvolutions; aPlayerEliminateIt++)
        {
            _players.pop_back();
        }

        // Evolve top players
        std::vector<std::shared_ptr<Core::Player> > aEvolvePlayers(_players .begin(), _players.begin() + _numOfEliminationEvolutions);
        _players.insert(std::end(_players), std::begin(aEvolvePlayers), std::end(aEvolvePlayers));

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
