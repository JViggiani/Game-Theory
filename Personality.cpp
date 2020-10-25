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
        unsigned int aRandomNumber = aIntDistribution(aRandomEngine);

        if(aMistakeChance > aRandomNumber)
        {
            //mistake!
            BOOST_LOG_TRIVIAL(trace) << "A player made a discision mistake!";

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
            BOOST_LOG_TRIVIAL(trace) << "A player avoided a mistake.";
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
            else if(aPlayerNumber == Data::ePlayerNumber::Two)
            {
                aDecision = aDecisionData.getPlayer1Decisions().back();
            }
            else
            {
                //player number not set
                throw std::exception("Player number not set in PersonalityCopycat::makeDecision");
            }
        }

        return calculateMistake(aDecision, aMistakeChance);
    }

    /*
        Vengeful
    */

    std::unique_ptr<Personality> PersonalityVengeful::clone() const
    {
        return std::make_unique<PersonalityVengeful>(*this);
    }

    Data::eDecisionType PersonalityVengeful::makeDecision(const Data::GameResults& aDecisionData, const Data::ePlayerNumber& aPlayerNumber, unsigned int aMistakeChance) const
    {
        Data::eDecisionType aDecision = Data::eDecisionType::Unset;
        
        if(aPlayerNumber == Data::ePlayerNumber::One)
        {
            aDecision = makePlayerDecision(aDecisionData.getPlayer2Decisions());
        }
        else if(aPlayerNumber == Data::ePlayerNumber::Two)
        {
            aDecision = makePlayerDecision(aDecisionData.getPlayer1Decisions());
        }
        else
        {
            //player number not set
            throw std::exception("Player number not set in PersonalityVengeful::makeDecision");
        }

        return calculateMistake(aDecision, aMistakeChance);
    }

    Data::eDecisionType PersonalityVengeful::makePlayerDecision(const std::vector<Data::eDecisionType>& aDecisionVector) const
    {
        if(std::find(aDecisionVector.begin(),
           aDecisionVector.end(),
           Data::eDecisionType::Cheat) != aDecisionVector.end())
        {
            return Data::eDecisionType::Cheat;
        }
        else
        {
            return Data::eDecisionType::Cooperate;
        }
    }

    /*
        Copykitten
    */

    std::unique_ptr<Personality> PersonalityCopykitten::clone() const
    {
        return std::make_unique<PersonalityCopykitten>(*this);
    }

    Data::eDecisionType PersonalityCopykitten::makeDecision(const Data::GameResults& aDecisionData, const Data::ePlayerNumber& aPlayerNumber, unsigned int aMistakeChance) const
    {
        Data::eDecisionType aDecision = Data::eDecisionType::Unset;

        if(aDecisionData.getPlayer1Decisions().size() < 2)
        {
            aDecision = Data::eDecisionType::Cooperate;
        }
        else
        {
            if(aPlayerNumber == Data::ePlayerNumber::One)
            {
                aDecision = makePlayerDecision(aDecisionData.getPlayer2Decisions());
            }
            else if(aPlayerNumber == Data::ePlayerNumber::Two)
            {
                aDecision = makePlayerDecision(aDecisionData.getPlayer1Decisions());
            }
            else
            {
                //player number not set
                throw std::exception("Player number not set in PersonalityCopycat::makeDecision");
            }
        }

        return calculateMistake(aDecision, aMistakeChance);
    }

    Data::eDecisionType PersonalityCopykitten::makePlayerDecision(const std::vector<Data::eDecisionType>& aDecisionVector) const
    {
        return aDecisionVector.back() == Data::eDecisionType::Cheat             //Last move was to cheat
            && *(++aDecisionVector.rbegin()) == Data::eDecisionType::Cheat ?    //And second to last move was to cheat
            Data::eDecisionType::Cheat : Data::eDecisionType::Cooperate;        //If so return cheat else cooperate
    }

    /*
        MeanCopycat
    */

    std::unique_ptr<Personality> PersonalityMeanCopycat::clone() const
    {
        return std::make_unique<PersonalityMeanCopycat>(*this);
    }

    Data::eDecisionType PersonalityMeanCopycat::makeDecision(const Data::GameResults& aDecisionData, const Data::ePlayerNumber& aPlayerNumber, unsigned int aMistakeChance) const
    {
        Data::eDecisionType aDecision = Data::eDecisionType::Unset;

        if(aDecisionData.getPlayer1Decisions().empty())
        {
            aDecision = Data::eDecisionType::Cheat;
        }
        else
        {
            if(aPlayerNumber == Data::ePlayerNumber::One)
            {
                aDecision = aDecisionData.getPlayer2Decisions().back();
            }
            else if(aPlayerNumber == Data::ePlayerNumber::Two)
            {
                aDecision = aDecisionData.getPlayer1Decisions().back();
            }
            else
            {
                //player number not set
                throw std::exception("Player number not set in PersonalityCopycat::makeDecision");
            }
        }

        return calculateMistake(aDecision, aMistakeChance);
    }

    /*
        PersonalityRandom
    */

    std::unique_ptr<Personality> PersonalityRandom::clone() const
    {
        return std::make_unique<PersonalityRandom>(*this);
    }

    Data::eDecisionType PersonalityRandom::makeDecision(const Data::GameResults& aDecisionData, const Data::ePlayerNumber& aPlayerNumber, unsigned int aMistakeChance) const
    {
        std::random_device aSeed;
        std::default_random_engine aRandomEngine(aSeed());
        std::uniform_int_distribution<int> aIntDistribution(0, 1);
        int aRandomNumber = aIntDistribution(aRandomEngine);

        if(aRandomNumber == 0)
        {
            return Data::eDecisionType::Cheat;
        }
        else if(aRandomNumber == 1)
        {
            return Data::eDecisionType::Cooperate;
        }
        else
        {
            throw std::exception("Personality Random generated an unexpected value!");
        }
    }

    /*
        PersonalityWinStayLoseSwitch
    */

    std::unique_ptr<Personality> PersonalityWinStayLoseSwitch::clone() const
    {
        return std::make_unique<PersonalityWinStayLoseSwitch>(*this);
    }

    Data::eDecisionType PersonalityWinStayLoseSwitch::makeDecision(const Data::GameResults& aDecisionData, const Data::ePlayerNumber& aPlayerNumber, unsigned int aMistakeChance) const
    {
        Data::eDecisionType aDecision = Data::eDecisionType::Unset;

        if(aDecisionData.getPlayer1Decisions().empty())
        {
            aDecision = Data::eDecisionType::Cooperate;
        }
        else
        {
            Data::eWinLose aWinLose = determineIfWinOrLose(aDecisionData, aPlayerNumber);

            if(aWinLose == Data::eWinLose::Win)
            {
                if(aPlayerNumber == Data::ePlayerNumber::One)
                {
                    aDecision = aDecisionData.getPlayer1Decisions().back();
                }
                else if(aPlayerNumber == Data::ePlayerNumber::Two)
                {
                    aDecision = aDecisionData.getPlayer2Decisions().back();
                }
                else
                {
                    //player number not set
                    throw std::exception("Player number not set in PersonalityWinStayLoseSwitch::makeDecision");
                }
            }
            else if(aWinLose == Data::eWinLose::Lose)
            {
                if(aPlayerNumber == Data::ePlayerNumber::One)
                {
                    aDecision = makePlayerLoseDecision(aDecisionData.getPlayer1Decisions());
                }
                else if(aPlayerNumber == Data::ePlayerNumber::Two)
                {
                    aDecision = makePlayerLoseDecision(aDecisionData.getPlayer2Decisions());
                }
                else
                {
                    //player number not set
                    throw std::exception("Player number not set in PersonalityWinStayLoseSwitch::makeDecision");
                }
            }
            else
            {
                throw std::exception("Win or lose was not correctly determined in PersonalityWinStayLoseSwitch::makeDecision");
            }
        }

        return calculateMistake(aDecision, aMistakeChance);
    }

    Data::eWinLose PersonalityWinStayLoseSwitch::determineIfWinOrLose(const Data::GameResults& aDecisionData, const Data::ePlayerNumber& aPlayerNumber) const
    {
        Data::eWinLose aWinLose = Data::eWinLose::Unset;
        
        if(aPlayerNumber == Data::ePlayerNumber::One)
        {
            if(aDecisionData.getPlayer1Reward().back() >= aDecisionData.getPlayer2Reward().back())
            {
                aWinLose = Data::eWinLose::Win;
            }
            else
            {
                aWinLose = Data::eWinLose::Lose;
            }
        }
        else if(aPlayerNumber == Data::ePlayerNumber::Two)
        {
            if(aDecisionData.getPlayer2Reward().back() >= aDecisionData.getPlayer1Reward().back())
            {
                aWinLose = Data::eWinLose::Win;
            }
            else
            {
                aWinLose = Data::eWinLose::Lose;
            }
        }
        else
        {
            throw std::exception("Player number not set in PersonalityWinStayLoseSwitch::makeDecision");
        }

        return aWinLose;
    }

    Data::eDecisionType PersonalityWinStayLoseSwitch::makePlayerLoseDecision(const std::vector<Data::eDecisionType>& aDecisionVector) const
    {
        if(aDecisionVector.back() == Data::eDecisionType::Cheat)
        {
            return Data::eDecisionType::Cooperate;
        }
        else if(aDecisionVector.back() == Data::eDecisionType::Cooperate)
        {
            return Data::eDecisionType::Cheat;
        }
        else
        {
            throw std::exception("Found a past decision which was not set in PersonalityWinStayLoseSwitch::makeDecision");
        }
    }
}