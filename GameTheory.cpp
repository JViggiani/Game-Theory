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
        //boost::log::keywords::file_name = "./Log/Sample.log",
        boost::log::keywords::file_name = aFileNamePath.c_str(),
        boost::log::keywords::format = "[%TimeStamp%] [%ThreadID%] [%Severity%] %Message%"
    );
    
    boost::log::core::get()->set_filter
    (  
        boost::log::trivial::severity >= aLoggingConfig._severity
    );

    boost::log::add_common_attributes();
}

int main(int argc, char* argv[])
{
    try
    {
        //Init logging
        Config::LoggingConfig aLoggingConfig;
        init_logging(aLoggingConfig);
        
        BOOST_LOG_TRIVIAL(info) << "Beginning main";

        Config::TournamentConfig aTournementConfig;

        Core::Tournament aTournament(aTournementConfig);

        Data::TournamentResults aTournamentResults = aTournament.run();
    }
    catch(std::exception e)
    {
        BOOST_LOG_TRIVIAL(info) << "Caught exception from main: " << e.what();
    }
    catch(...)
    {
        BOOST_LOG_TRIVIAL(info) << "Caught unknown exception from main.";
    }
}