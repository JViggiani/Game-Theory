#include "Personality.hpp"

#include <random>
#include <string>
#include <iostream>
#include <functional>

#include <boost/log/trivial.hpp>

namespace Implementation
{
    /*
        Common
    */
    Data::eDecisionType Personality::calculateMistake(const Data::eDecisionType& aCurrentDecision, unsigned int aMistakeChance) const
    {
        Data::eDecisionType aNewDecision = aCurrentDecision;
        
        std::random_device aSeed;
        std::default_random_engine aRandomEngine(aSeed());
        std::uniform_int_distribution<int> aIntDistribution(0, 99);
        int aRandomNumber = aIntDistribution(aRandomEngine);

        std::cout << std::to_string(aRandomNumber) << "\n";

        if(aMistakeChance > aRandomNumber)
        {
            //mistake!
            BOOST_LOG_TRIVIAL(debug) << "A player made a discision mistake!";

            if(aCurrentDecision == Data::eDecisionType::Cheat)
            {
                aNewDecision = Data::eDecisionType::Cooperate;
            }
            else if(aCurrentDecision == Data::eDecisionType::Cooperate)
            {
                aNewDecision = Data::eDecisionType::Cheat;
            }
            else
            {
                //we had an unset decision as input
                throw std::exception("Unset decision in Personality::calculateMistake. Could not calculate mistake!");
            }
        }
        else
        {
            BOOST_LOG_TRIVIAL(debug) << "A player avoided a mistake.";
        }

        return aNewDecision;
    }

    /*
        Cheater
    */
    std::unique_ptr<Personality> PersonalityCheater::clone() const
    {
        return std::make_unique<PersonalityCheater>(*this);
    }

    Data::eDecisionType PersonalityCheater::makeDecision(const Data::GameResults& aDecisionData, const Data::ePlayerNumber& aPlayerNumber, unsigned int aMistakeChance) const
    {
        Data::eDecisionType aDecision = Data::eDecisionType::Cheat;
        
        aDecision = calculateMistake(aDecision, aMistakeChance);

        return calculateMistake(aDecision, aMistakeChance);
    }

    /*
        Cooperator
    */

    std::unique_ptr<Personality> PersonalityCooperator::clone() const
    {
        return std::make_unique<PersonalityCooperator>(*this);
    }

    Data::eDecisionType PersonalityCooperator::makeDecision(const Data::GameResults& aDecisionData, const Data::ePlayerNumber& aPlayerNumber, unsigned int aMistakeChance) const
    {
        Data::eDecisionType aDecision = Data::eDecisionType::Cooperate;

        aDecision = calculateMistake(aDecision, aMistakeChance);

        return calculateMistake(aDecision, aMistakeChance);
    }

    /*
        Copycat
    */

    std::unique_ptr<Personality> PersonalityCopycat::clone() const
    {
        return std::make_unique<PersonalityCopycat>(*this);
    }

    Data::eDecisionType PersonalityCopycat::makeDecision(const Data::GameResults& aDecisionData, const Data::ePlayerNumber& aPlayerNumber, unsigned int aMistakeChance) const
    {
        Data::eDecisionType aDecision = Data::eDecisionType::Unset;
        
        if(aDecisionData.getPlayer1Decisions().empty())
        {
            aDecision = Data::eDecisionType::Cooperate;
        }
        else
        {
            if(aPlayerNumber == Data::ePlayerNumber::One)
            {
                aDecision = aDecisionData.getPlayer2Decisions().back();
            }
            else
            {
                aDecision = aDecisionData.getPlayer1Decisions().back();
            }
        }

        return calculateMistake(aDecision, aMistakeChance);
    }

}