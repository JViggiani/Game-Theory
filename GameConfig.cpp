#include "GameConfig.hpp"

#include <boost/log/trivial.hpp>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

Config::GameConfig::GameConfig()
{
    BOOST_LOG_TRIVIAL(debug) << "Building game machine and reading game config file.";
    
    boost::property_tree::ptree pt;
    boost::property_tree::ini_parser::read_ini("./Config/TournamentConfig.ini", pt);

    _bothCheat = pt.get<int>("Game.BothCheat");
    _bothCooperate = pt.get<int>("Game.BothCooperate");
    _cheat = pt.get<int>("Game.Cheat");
    _cooperate = pt.get<int>("Game.Cooperate");
    _mistakeChance = pt.get<int>("Game.MistakeChance");

    if(_mistakeChance < 0 || _mistakeChance > 100)
    {
        throw std::exception("Mistake chance config is lower than 0% or greater than 100%!");
    }
}
