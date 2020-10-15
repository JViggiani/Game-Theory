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

    Data::eDecisionType PersonalityCheater::makeDecision(const Data::GameResults& aDecisionData, const Data::ePlayerNumber& aPlayerNumber) const
    {
        return Data::eDecisionType::Cheat;
    }

    /*
        Cooperator
    */

    std::unique_ptr<Personality> PersonalityCooperator::clone() const
    {
        return std::make_unique<PersonalityCooperator>(*this);
    }

    Data::eDecisionType PersonalityCooperator::makeDecision(const Data::GameResults& aDecisionData, const Data::ePlayerNumber& aPlayerNumber) const
    {
        return Data::eDecisionType::Cooperate;
    }

    /*
        Copycat
    */

    std::unique_ptr<Personality> PersonalityCopycat::clone() const
    {
        return std::make_unique<PersonalityCopycat>(*this);
    }

    Data::eDecisionType PersonalityCopycat::makeDecision(const Data::GameResults& aDecisionData, const Data::ePlayerNumber& aPlayerNumber) const
    {
        if(aDecisionData.getPlayer1Decisions().empty())
        {
            return Data::eDecisionType::Cooperate;
        }

        if(aPlayerNumber == Data::ePlayerNumber::One)
        {
            return aDecisionData.getPlayer2Decisions().back();
        }
        else
        {
            return aDecisionData.getPlayer1Decisions().back();
        }
    }

}