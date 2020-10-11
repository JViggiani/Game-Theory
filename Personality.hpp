#pragma once

#include <memory>

#include "Decision.hpp"

class Personality
{
public:
	virtual std::unique_ptr<Personality> clone() const = 0;
	virtual Decision makeDecision() const = 0;

	virtual ~Personality() = default;
};

class PersonalityCheater : public Personality
{
public:
	virtual std::unique_ptr<Personality> clone() const override;

	Decision makeDecision() const override;
};