#include "LoggingConfig.hpp"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

#include <string>

Config::LoggingConfig::LoggingConfig()
{
	boost::property_tree::ptree pt;
	boost::property_tree::ini_parser::read_ini("./Config/LoggingConfig.ini", pt);

	_severity = static_cast<boost::log::trivial::severity_level>(pt.get<int>("Logging.Severity"));

	_logFileName = pt.get<std::string>("Logging.LogFileName");
	_logFileDirectory = pt.get<std::string>("Logging.LogFileDirectory");
}
