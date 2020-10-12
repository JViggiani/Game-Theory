#include "Machine.hpp"

Machine* Machine::pinstance_{nullptr};
std::mutex Machine::mutex_;

Machine::Machine()
{
    //JOSH read reward config from file ONCE here
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
