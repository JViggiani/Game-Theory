#include "Machine.hpp"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

#include <boost/log/trivial.hpp>

namespace Core
{

    Machine* Machine::pinstance_{nullptr};
    std::mutex Machine::mutex_;

    Machine* Machine::GetInstance()
    {
        std::lock_guard<std::mutex> lock(mutex_);
        if(pinstance_ == nullptr)
        {
            pinstance_ = new Machine();
        }
        return pinstance_;
    }

    Data::RoundResults Machine::processRound(const std::shared_ptr<Player>& aPlayer1, const std::shared_ptr<Player>& aPlayer2, const Data::GameResults& aGameResults)
    {
        Data::eDecisionType aPlayer1Decision = aPlayer1->makeDecision(aGameResults, Data::ePlayerNumber::One, _gameConfig._mistakeChance);
        Data::eDecisionType aPlayer2Decision = aPlayer2->makeDecision(aGameResults, Data::ePlayerNumber::Two, _gameConfig._mistakeChance);

        Data::RoundResults aRoundResults(aPlayer1Decision, aPlayer2Decision, _gameConfig);
        return aRoundResults;
    }

}