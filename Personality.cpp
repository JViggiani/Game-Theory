#include "Personality.hpp"

/*
    Cheater
*/
std::unique_ptr<Personality> PersonalityCheater::clone() const
{
    return std::make_unique<PersonalityCheater>(*this);
}

Decision PersonalityCheater::makeDecision() const
{
    return Decision::Cheat;
}

/*
    Cooperator
*/


