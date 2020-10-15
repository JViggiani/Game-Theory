#include "Personality.hpp"

namespace Implementation
{

    /*
        Cheater
    */
    std::unique_ptr<Personality> PersonalityCheater::clone() const
    {
        return std::make_unique<PersonalityCheater>(*this);
    }

    Data::Decision PersonalityCheater::makeDecision(const Data::GameResults& aDecisionData, const Data::PlayerNumber& aPlayerNumber) const
    {
        return Data::Decision::Cheat;
    }

    /*
        Cooperator
    */

    std::unique_ptr<Personality> PersonalityCooperator::clone() const
    {
        return std::make_unique<PersonalityCooperator>(*this);
    }

    Data::Decision PersonalityCooperator::makeDecision(const Data::GameResults& aDecisionData, const Data::PlayerNumber& aPlayerNumber) const
    {
        return Data::Decision::Cooperate;
    }

    /*
        Copycat
    */

    std::unique_ptr<Personality> PersonalityCopycat::clone() const
    {
        return std::make_unique<PersonalityCopycat>(*this);
    }

    Data::Decision PersonalityCopycat::makeDecision(const Data::GameResults& aDecisionData, const Data::PlayerNumber& aPlayerNumber) const
    {
        if(aDecisionData.getPlayer1Decisions().empty())
        {
            return Data::Decision::Cooperate;
        }

        if(aPlayerNumber == Data::PlayerNumber::One)
        {
            return aDecisionData.getPlayer2Decisions().back();
        }
        else
        {
            return aDecisionData.getPlayer1Decisions().back();
        }
    }

}