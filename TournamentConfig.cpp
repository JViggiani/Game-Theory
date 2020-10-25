#include "TournamentConfig.hpp"

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

namespace Config
{
	
	Config::TournamentConfig::TournamentConfig()
	{
		BOOST_LOG_TRIVIAL(debug) << "Reading Tournament config";
		
		boost::property_tree::ptree pt;
		boost::property_tree::ini_parser::read_ini("./Config/TournamentConfig.ini", pt);

		// Tournament Config
		_numOfEvolutions = pt.get<int>("Tournament.Evolutions");
		_numOfRounds = pt.get<int>("Tournament.Rounds");
		_numOfEliminationEvolutions = pt.get<int>("Tournament.EliminationEvolutions");

		//Personalities
		_numCheaters = pt.get<int>("Players.Cheaters");
		_numCooperators = pt.get<int>("Players.Cooperators");
		_numCopycats = pt.get<int>("Players.Copycats");
		_numVengeful = pt.get<int>("Players.Vengeful");
		_numCopykitten = pt.get<int>("Players.Copykitten");
		_numMeanCopycat = pt.get<int>("Players.MeanCopycat");
		_numRandom = pt.get<int>("Players.Random");
		_numWinStayLoseSwitch = pt.get<int>("Players.WinStayLoseSwitch");

		if(_numCheaters + _numCooperators + _numCopycats / 2 < _numOfEliminationEvolutions)
		{
			throw std::exception("Cannot set up tournament. Number of players to eliminate and duplicate is too high compared to the number of players. Increase number of players or reduce the number to be eliminated/duplicated each round.");
		}
	}
}


