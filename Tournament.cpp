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
        
        _numOfEvolutions = aTournamentConfig._numOfEvolutions;

        _numOfRounds = aTournamentConfig._numOfRounds;

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

        BOOST_LOG_TRIVIAL(info) << "Finishing Tournament";
        
        return Data::TournamentResults();
	}

}
