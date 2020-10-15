#pragma once

#include <boost/log/trivial.hpp>

namespace Config
{
	
	struct LoggingConfig
	{
		LoggingConfig();

		~LoggingConfig() = default;

		boost::log::trivial::severity_level _severity;
		std::string _logFileName;
		std::string _logFileDirectory;
	};

}



