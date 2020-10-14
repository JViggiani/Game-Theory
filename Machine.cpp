#include "Machine.hpp"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

#include <boost/log/trivial.hpp>

Machine* Machine::pinstance_{nullptr};
std::mutex Machine::mutex_;

Machine::Machine()
{
    //In the constructor we read the reward.ini file to determine game reward

    BOOST_LOG_TRIVIAL(info) << "Building game machine and reading reward config file.";

    boost::property_tree::ptree pt;
    boost::property_tree::ini_parser::read_ini("./Config/RewardConfig.ini", pt);

    _rewardConfig._bothCheat = pt.get<int>("Reward.BothCheat");
    _rewardConfig._bothCooperate = pt.get<int>("Reward.BothCooperate");
    _rewardConfig._cheat = pt.get<int>("Reward.Cheat");
    _rewardConfig._cooperate = pt.get<int>("Reward.Cooperate");
}

Machine* Machine::GetInstance()
{
    std::lock_guard<std::mutex> lock(mutex_);
    if(pinstance_ == nullptr)
    {
        pinstance_ = new Machine();
    }
    return pinstance_;
}

RoundResults Machine::processRound(const std::shared_ptr<Player>& aPlayer1, const std::shared_ptr<Player>& aPlayer2, const GameResults& aGameResults)
{    
    Decision aPlayer1Decision = aPlayer1->makeDecision(aGameResults, PlayerNumber::One);
    Decision aPlayer2Decision = aPlayer2->makeDecision(aGameResults, PlayerNumber::Two);

    RoundResults aRoundResults(aPlayer1Decision, aPlayer2Decision, _rewardConfig);
    return aRoundResults;
}
