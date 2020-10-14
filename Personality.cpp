#include "Personality.hpp"

/*
    Cheater
*/
std::unique_ptr<Personality> PersonalityCheater::clone() const
{
    return std::make_unique<PersonalityCheater>(*this);
}

Decision PersonalityCheater::makeDecision(const GameResults& aDecisionData, const PlayerNumber& aPlayerNumber) const
{
    return Decision::Cheat;
}

/*
    Cooperator
*/

std::unique_ptr<Personality> PersonalityCooperator::clone() const
{
    return std::make_unique<PersonalityCooperator>(*this);
}

Decision PersonalityCooperator::makeDecision(const GameResults& aDecisionData, const PlayerNumber& aPlayerNumber) const
{
    return Decision::Cooperate;
}

/*
    Copycat
*/

std::unique_ptr<Personality> PersonalityCopycat::clone() const
{
    return std::make_unique<PersonalityCopycat>(*this);
}

Decision PersonalityCopycat::makeDecision(const GameResults& aDecisionData, const PlayerNumber& aPlayerNumber) const
{
    if(aDecisionData.getPlayer1Decisions().empty())
    {
        return Decision::Cooperate;
    }

    if(aPlayerNumber == PlayerNumber::One)
    {
        return aDecisionData.getPlayer2Decisions().back();
    }
    else
    {
        return aDecisionData.getPlayer1Decisions().back();
    }
}
