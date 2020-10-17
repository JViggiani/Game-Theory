#pragma once

#include "ePersonalityType.hpp"
#include "Player.hpp"

#include <map>
#include <vector>
#include <memory>

namespace Data
{

	struct TournamentResults
	{
		TournamentResults(const std::vector<std::shared_ptr<Core::Player> >& aPlayerVector);
		~TournamentResults() = default;

		std::map<Data::ePersonalityType, int> _tournamentEndPlayerComposition;
	};

}

