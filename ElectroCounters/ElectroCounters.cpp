/**
  ******************************************************************************
* @attention
 *
 * Copyright (c) 2024, Dzmitry Kushniaruk <xdzmkus@gmail.com>
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include "Counter.h"
#include "Surveable.h"

#include <Poco/AutoPtr.h>
#include <Poco/Util/IniFileConfiguration.h>

#include <Poco/Data/MySQL/MySQLException.h>
#include <Poco/Data/MySQL/Connector.h>
#include <Poco/Data/Session.h>
#include <Poco/Data/Statement.h>

#include <iostream>
#include <string>
#include <thread>
#include <vector>

using namespace Poco::Util;
using namespace Poco::Data::Keywords;

int main(int argc, char* argv[])
{
	// Read the configuration.
	std::string configFile;

	if (argc > 1) { configFile = argv[1]; }
	else { configFile = "config.ini"; }

	Poco::AutoPtr<IniFileConfiguration> config;
	try
	{
		config = new IniFileConfiguration(configFile);
	}
	catch (Poco::IOException&)
	{
		std::cout << "Main: I/O exception when opening configuration file: " << configFile << ". Aborting...";
		return 1;
	}

	const std::string connectionString = format("host={};port={};user={};password={};db={}", 
		config->getString("MySQL.host", "localhost"),
		config->getString("MySQL.port", "3306"),
		config->getString("MySQL.user", ""),
		config->getString("MySQL.password", ""),
		config->getString("MySQL.db", "")
		);

	// Survey the counters

	std::vector<std::thread> surveyThreads;
	Surveable counterThread(connectionString);
	Counter cnt{};

	try
	{
		Poco::Data::MySQL::Connector::registerConnector();

		Poco::Data::Session session("MySQL", connectionString);
		
		// Запрос к базе оптимизирован в соответствии с используемыми далее значениями!!!
		Poco::Data::Statement select = (session << "SELECT id_counter, ip, port, zn, sa, protocol \
													FROM counters \
													WHERE ip != 0 AND ip IS NOT NULL \
														AND port != 0 AND port IS NOT NULL \
														AND id_uspd = 0 \
														AND 30m = 1 \
														AND is_include_survey = 1",
			into(cnt.id), into(cnt.ip),	into(cnt.port),	into(cnt.zn), into(cnt.sa), into(cnt.protocol),
			range(0, 1) //  iterate over result set one row at a time
			);

		while (!select.done())
		{
			select.execute();

			surveyThreads.push_back(std::thread(counterThread, cnt));
		}
	}
	catch (Poco::Data::DataException& e)
	{
		std::cerr << "MySQL Error: " << e.displayText() << std::endl;
	}

	// wait all threads
	for (auto &thr : surveyThreads)
	{
		if (thr.joinable())
			thr.join();
	}

	return 0;
}
