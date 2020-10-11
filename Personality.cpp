#include "Personality.hpp"

/*
    Cheater
*/

Decision PersonalityCheater::makeDecision() const
{
    return Decision::Cheat;
}

/*
    Cooperator
*/

std::unique_ptr<Personality> PersonalityCheater::clone() const
{
    return std::unique_ptr<Personality>();
}
