#include "TournamentResults.hpp"

Data::TournamentResults::TournamentResults(const std::vector<std::shared_ptr<Core::Player> >& aPlayerVector)
{
	for(auto aPlayer : aPlayerVector)
	{
		if(_tournamentEndPlayerComposition.find(aPlayer->getPersonalityType()) != _tournamentEndPlayerComposition.end())
		{
			//counter found
			_tournamentEndPlayerComposition[aPlayer->getPersonalityType()]++;
		}
		else
		{
			_tournamentEndPlayerComposition.insert(std::make_pair(aPlayer->getPersonalityType(), 1));
		}
	}
}
