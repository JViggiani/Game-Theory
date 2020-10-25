#pragma once

#include <memory>
#include <vector>

#include "GameResults.hpp"
#include "ePlayerNumber.hpp"
#include "eWinLose.hpp"

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
		virtual Data::eDecisionType makeDecision(const Data::GameResults& aDecisionData, const Data::ePlayerNumber& aPlayerNumber, unsigned int aMistakeChance) const = 0;

	protected:
		Data::eDecisionType calculateMistake(const Data::eDecisionType& aCurrentDecision, unsigned int aMistakeChance) const;
	};

	class PersonalityCheater final : public Personality
	{
	public:
		virtual std::unique_ptr<Personality> clone() const override;

		Data::eDecisionType makeDecision(const Data::GameResults& aDecisionData, const Data::ePlayerNumber& aPlayerNumber, unsigned int aMistakeChance) const override;
	};

	class PersonalityCooperator final : public Personality
	{
	public:
		virtual std::unique_ptr<Personality> clone() const override;

		Data::eDecisionType makeDecision(const Data::GameResults& aDecisionData, const Data::ePlayerNumber& aPlayerNumber, unsigned int aMistakeChance) const override;
	};

	class PersonalityCopycat final : public Personality
	{
	public:
		virtual std::unique_ptr<Personality> clone() const override;

		Data::eDecisionType makeDecision(const Data::GameResults& aDecisionData, const Data::ePlayerNumber& aPlayerNumber, unsigned int aMistakeChance) const override;
	};

	class PersonalityVengeful final : public Personality
	{
	public:
		virtual std::unique_ptr<Personality> clone() const override;

		Data::eDecisionType makeDecision(const Data::GameResults& aDecisionData, const Data::ePlayerNumber& aPlayerNumber, unsigned int aMistakeChance) const override;

	private:
		Data::eDecisionType makePlayerDecision(const std::vector<Data::eDecisionType>& aDecisionVector) const;
	};

	class PersonalityCopykitten final : public Personality
	{
	public:
		virtual std::unique_ptr<Personality> clone() const override;

		Data::eDecisionType makeDecision(const Data::GameResults& aDecisionData, const Data::ePlayerNumber& aPlayerNumber, unsigned int aMistakeChance) const override;

	private:
		Data::eDecisionType makePlayerDecision(const std::vector<Data::eDecisionType>& aDecisionVector) const;
	};

	class PersonalityMeanCopycat final : public Personality
	{
	public:
		virtual std::unique_ptr<Personality> clone() const override;

		Data::eDecisionType makeDecision(const Data::GameResults& aDecisionData, const Data::ePlayerNumber& aPlayerNumber, unsigned int aMistakeChance) const override;
	};

	class PersonalityRandom final : public Personality
	{
	public:
		virtual std::unique_ptr<Personality> clone() const override;

		Data::eDecisionType makeDecision(const Data::GameResults& aDecisionData, const Data::ePlayerNumber& aPlayerNumber, unsigned int aMistakeChance) const override;
	};

	class PersonalityWinStayLoseSwitch final : public Personality
	{
	public:
		virtual std::unique_ptr<Personality> clone() const override;

		Data::eDecisionType makeDecision(const Data::GameResults& aDecisionData, const Data::ePlayerNumber& aPlayerNumber, unsigned int aMistakeChance) const override;
	private:
		Data::eWinLose determineIfWinOrLose(const Data::GameResults& aDecisionData, const Data::ePlayerNumber& aPlayerNumber) const;
	
		Data::eDecisionType makePlayerLoseDecision(const std::vector<Data::eDecisionType>& aDecisionVector) const;
	};

}