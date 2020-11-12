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
		_processConfig._numOfEvolutions = pt.get<int>("Tournament.Evolutions");
		_processConfig._numOfRounds = pt.get<int>("Tournament.Rounds");
		_processConfig._numOfEliminationEvolutions = pt.get<int>("Tournament.EliminationEvolutions");

		//Personalities
		_playerConfig._numCheaters = pt.get<int>("Players.Cheaters");
		_playerConfig._numCooperators = pt.get<int>("Players.Cooperators");
		_playerConfig._numCopycats = pt.get<int>("Players.Copycats");
		_playerConfig._numVengeful = pt.get<int>("Players.Vengeful");
		_playerConfig._numCopykitten = pt.get<int>("Players.Copykitten");
		_playerConfig._numMeanCopycat = pt.get<int>("Players.MeanCopycat");
		_playerConfig._numRandom = pt.get<int>("Players.Random");
		_playerConfig._numWinStayLoseSwitch = pt.get<int>("Players.WinStayLoseSwitch");

		if(_playerConfig._numCheaters + _playerConfig._numCooperators + _playerConfig._numCopycats
		   + _playerConfig._numCopykitten + _playerConfig._numMeanCopycat + _playerConfig._numRandom
		   + _playerConfig._numVengeful + _playerConfig._numWinStayLoseSwitch / 2 < _processConfig._numOfEliminationEvolutions)
		{
			throw std::exception("Cannot set up tournament. Number of players to eliminate and duplicate is too high compared to the number of players. Increase number of players or reduce the number to be eliminated/duplicated each round.");
		}
	}
}


