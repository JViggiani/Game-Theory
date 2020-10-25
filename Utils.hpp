#pragma once

namespace Utils
{
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
}