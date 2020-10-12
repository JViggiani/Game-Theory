#pragma once

#include <memory>
#include <vector>

#include "GameResults.hpp"
#include "PlayerNumber.hpp"

class Personality
{
public:
	virtual std::unique_ptr<Personality> clone() const = 0;
	virtual Decision makeDecision(const GameResults& aDecisionData, const PlayerNumber& aPlayerNumber) const = 0;

	virtual ~Personality() = default;
};

class PersonalityCheater : public Personality
{
public:
	virtual std::unique_ptr<Personality> clone() const override;

	Decision makeDecision(const GameResults& aDecisionData, const PlayerNumber& aPlayerNumber) const override;
};

class PersonalityCooperator : public Personality
{
public:
	virtual std::unique_ptr<Personality> clone() const override;

	Decision makeDecision(const GameResults& aDecisionData, const PlayerNumber& aPlayerNumber) const override;
};

class PersonalityCopycat : public Personality
{
public:
	virtual std::unique_ptr<Personality> clone() const override;

	Decision makeDecision(const GameResults& aDecisionData, const PlayerNumber& aPlayerNumber) const override;
};