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
		BOOST_LOG_TRIVIAL(info) << "Reading Tournament config";
		
		boost::property_tree::ptree pt;
		boost::property_tree::ini_parser::read_ini("./Config/TournamentConfig.ini", pt);

		// Tournament Config
		_numOfEvolutions = pt.get<int>("Tournament.Evolutions");
		_numOfRounds = pt.get<int>("Tournament.Rounds");

		//Personalities
		_numCheaters = pt.get<int>("Players.Cheaters");
		_numCooperators = pt.get<int>("Players.Cooperators");
		_numCopycats = pt.get<int>("Players.Copycats");
	}
}


