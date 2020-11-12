#pragma once

#include "PlayerConfig.hpp"
#include "ProcessConfig.hpp"

namespace Config
{
	
	struct TournamentConfig
	{
		TournamentConfig();
		~TournamentConfig() = default;

		// Process Config
		ProcessConfig _processConfig;

		// Personalities
		PlayerConfig _playerConfig;
	};

}
