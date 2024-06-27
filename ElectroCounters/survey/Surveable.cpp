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
#include "Surveable.h"

#include "protocols/ProtocolExchange.h"
#include "protocols/CC301_1/CC301_1.h"

#include <Poco/DateTime.h>
#include <Poco/Data/Session.h>
#include <Poco/Data/Statement.h>
#include <Poco/Exception.h>
#include <Poco/Data/MySQL/MySQLException.h>

#include <iostream>
#include <mutex>
#include <memory>

using namespace Poco::Data::Keywords;

static std::mutex coutMutex;

Surveable::Surveable(const std::string& connectionString) : connStr(connectionString)
{
}

Surveable::~Surveable()
{
}

// thread's entry point
void Surveable::operator()(Counter counter) const
{
	coutMutex.lock();
	std::cout << "Get DateTime from " << static_cast<std::string>(counter) << std::endl;
	coutMutex.unlock();

	try
	{
		// request Date and Time from the counter
		Poco::DateTime dt = requestDateTime(counter);

		// store received Date and Time in the database
		storeDateTime(counter, dt);

		coutMutex.lock();
		std::cout << "Received DateTime from " << static_cast<std::string>(counter) << std::endl;
		coutMutex.unlock();
	}
	catch (const Poco::Data::DataException& e)
	{
		coutMutex.lock();
		std::cerr << static_cast<std::string>(counter) << " MySQL Error: " << e.displayText() << std::endl;
		coutMutex.unlock();
	}
	catch (const Poco::Exception& e)
	{
		coutMutex.lock();
		std::cerr << static_cast<std::string>(counter) << " Communication Error: " << e.displayText() << std::endl;
		coutMutex.unlock();
	}
}

// request date and time from counter via tcp/ip
Poco::DateTime Surveable::requestDateTime(const Counter& cnt) const
{
	std::unique_ptr<ProtocolExchange> protoEx;
	
	if (cnt.protocol.isNull())
	{
		throw Poco::Exception("Unknown counter's protocol");
	}

	// Should Use Factory in the future
	if (cnt.protocol.value() == "CC301_1")
	{
		protoEx = std::make_unique<CC301_1>(cnt);
	}
	else
	{
		throw Poco::Exception("Unsupported counter's protocol");
	}

	return protoEx->readDateTime();
}

// store date and time from counter into database
void Surveable::storeDateTime(Counter& cnt, Poco::DateTime& dt) const
{
	Poco::Data::Session session("MySQL", connStr);

	// Запрос к базе оптимизирован!!!
	Poco::Data::Statement insert = (session << "INSERT INTO get_time (id_counter, time, zn, sa, protocol) VALUES (?, ?, ?, ?, ?)",
		use(cnt.id), use(dt), use(cnt.zn), use(cnt.sa), use(cnt.protocol));

	insert.execute();
}

