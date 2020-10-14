// Game Theory.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <memory>

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

#include "Game.hpp"

void init_logging()
{
    boost::log::register_simple_formatter_factory<boost::log::trivial::severity_level, char>("Severity");

    boost::log::add_file_log
    (
        boost::log::keywords::file_name = "sample.log",
        boost::log::keywords::format = "[%TimeStamp%] [%ThreadID%] [%Severity%] %Message%"
    );

    boost::log::core::get()->set_filter
    (
        boost::log::trivial::severity >= boost::log::trivial::info
    );

    boost::log::add_common_attributes();
}

int main(int argc, char* argv[])
{
    init_logging();
    
    try
    {
        BOOST_LOG_TRIVIAL(info) << "Beginning main";

        //PersonalityCheater aCheater;
        PersonalityCooperator aCooperator;
        PersonalityCopycat aCopycat;
        
        Player aPlayer1(aCooperator);
        Player aPlayer2(aCopycat);
        
        //std::shared_ptr<Player> aPlayer3Ptr = std::make_shared<Player>(aCheater);
        std::shared_ptr<Player> aPlayer1Ptr = std::make_shared<Player>(aPlayer1);
        std::shared_ptr<Player> aPlayer2Ptr = std::make_shared<Player>(aPlayer2);
        
        Core::Game aGame(aPlayer1Ptr, aPlayer2Ptr, 10);
        GameResults aGameResults = aGame.run();
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