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

void init_logging(const Config::LoggingConfig& aLoggingConfig)
{
    boost::log::register_simple_formatter_factory<boost::log::trivial::severity_level, char>("Severity");

    std::string aFileNamePath = "./" + aLoggingConfig._logFileDirectory + "/" + aLoggingConfig._logFileName + ".log";

    boost::log::add_file_log
    (
        boost::log::keywords::file_name = aFileNamePath.c_str(),
        boost::log::keywords::format = "[%TimeStamp%] [%ThreadID%] [%Severity%] %Message%"
    );
    
    boost::log::core::get()->set_filter
    (  
        boost::log::trivial::severity >= aLoggingConfig._severity
    );

    boost::log::add_common_attributes();
}

void printTournamentResults(const Data::TournamentResults& aTournamentResults)
{
    BOOST_LOG_TRIVIAL(info) << "Tournament results:";

    for(auto aPersonalityType : aTournamentResults._tournamentEndPlayerComposition)
    {
        BOOST_LOG_TRIVIAL(info) << "Personality " << std::to_string(static_cast<int>(aPersonalityType.first)) << " count:" << std::to_string(aPersonalityType.second);
    }
}

int main(int argc, char* argv[])
{
    try
    {
        //Init logging
        Config::LoggingConfig aLoggingConfig;
        init_logging(aLoggingConfig);
        
        BOOST_LOG_TRIVIAL(debug) << "Beginning main.";

        //Build and run tournament
        Config::TournamentConfig aTournementConfig;
        Core::Tournament aTournament(aTournementConfig);
        Data::TournamentResults aTournamentResults = aTournament.run();

        printTournamentResults(aTournamentResults);

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