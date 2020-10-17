#pragma once

namespace Config
{
	
	struct TournamentConfig
	{
		TournamentConfig();
		~TournamentConfig() = default;

		// Tournament Config
		int _numOfEvolutions;
		int _numOfRounds;
		int _numOfEliminationEvolutions;

		//Personalities
		int _numCheaters;
		int _numCooperators;
		int _numCopycats;
	};

}
