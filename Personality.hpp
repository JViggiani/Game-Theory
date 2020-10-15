#pragma once

#include <memory>
#include <vector>

#include "GameResults.hpp"
#include "PlayerNumber.hpp"

namespace Implementation
{

	//! Abstract base Personality
	class Personality
	{
	public:
		/// Constructors and Destructors ///

		//! Main constructor.
		Personality() = default;

		//! Default destructor.
		virtual ~Personality() = default;

		//! Default copy constructor
		Personality(const Personality&) = default;

		//! Default move constructor
		Personality(Personality&&) = default;

		/// Operators ///

		//! Default copy assignment
		Personality& operator=(const Personality&) = default;

		//! Default move assignment
		Personality& operator=(Personality&&);

		/// Functions ///

		virtual std::unique_ptr<Personality> clone() const = 0;
		virtual Data::Decision makeDecision(const Data::GameResults& aDecisionData, const Data::PlayerNumber& aPlayerNumber) const = 0;
	};

	class PersonalityCheater : public Personality
	{
	public:
		virtual std::unique_ptr<Personality> clone() const override;

		Data::Decision makeDecision(const Data::GameResults& aDecisionData, const Data::PlayerNumber& aPlayerNumber) const override;
	};

	class PersonalityCooperator : public Personality
	{
	public:
		virtual std::unique_ptr<Personality> clone() const override;

		Data::Decision makeDecision(const Data::GameResults& aDecisionData, const Data::PlayerNumber& aPlayerNumber) const override;
	};

	class PersonalityCopycat : public Personality
	{
	public:
		virtual std::unique_ptr<Personality> clone() const override;

		Data::Decision makeDecision(const Data::GameResults& aDecisionData, const Data::PlayerNumber& aPlayerNumber) const override;
	};

}