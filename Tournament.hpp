#pragma once

#include "TournamentConfig.hpp"
#include "TournamentResults.hpp"
#include "Player.hpp"

#include <vector>

namespace Core
{

	class Tournament
	{
	public:

		///	Constructors and Destructors ///

		//! Main constructor.
		Tournament(const Config::TournamentConfig& aTournamentConfig);

		//! Default destructor.
		~Tournament() = default;

		//! Default copy constructor
		Tournament(const Tournament&) = default;

		//! Default move constructor
		Tournament(Tournament&&) = default;

		///	Operators ///

		//! Default copy assignment
		Tournament& operator=(const Tournament&) = default;

		//! Default move assignment
		Tournament& operator=(Tournament&&);

		///	Functions ///

		Data::TournamentResults run();

	private:
		std::vector<std::shared_ptr<Core::Player> > _players;
		int _numOfEvolutions;
		int _numOfRounds;
	};
}