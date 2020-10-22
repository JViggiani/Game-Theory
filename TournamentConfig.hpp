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
		int _numVengeful;
		int _numCopykitten;
		int _numMeanCopycat;
		int _numRandom;
		int _numWinStayLoseSwitch;
	};

}
