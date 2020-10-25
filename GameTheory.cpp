// Game Theory.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <memory>

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

#include "Game.hpp"
#include "TournamentConfig.hpp"
#include "LoggingConfig.hpp"
#include "Tournament.hpp"
#include "Utils.hpp"

int main(int argc, char* argv[])
{
    try
    {
        //Init logging
        Config::LoggingConfig aLoggingConfig;
        Utils::init_logging(aLoggingConfig);
        
        BOOST_LOG_TRIVIAL(debug) << "Beginning main.";

        //Build and run tournament
        Config::TournamentConfig aTournementConfig;
        Core::Tournament aTournament(aTournementConfig);
        Data::TournamentResults aTournamentResults = aTournament.run();

        Utils::printTournamentResults(aTournamentResults);

        BOOST_LOG_TRIVIAL(debug) << "Finishing main.";
    }
    catch(std::exception e)
    {
        BOOST_LOG_TRIVIAL(error) << "Caught exception from main: " << e.what();
    }
    catch(...)
    {
        BOOST_LOG_TRIVIAL(error) << "Caught unknown exception from main.";
    }
}