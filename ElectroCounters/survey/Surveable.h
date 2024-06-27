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

#pragma once

#include "Counter.h"

#include <Poco/DateTime.h>

#include <string>

class Surveable
{
public:
	Surveable(const std::string& connectionString);

	~Surveable();

	void operator()(Counter counter) const;

protected:

	Poco::DateTime requestDateTime(const Counter& cnt) const;

	void storeDateTime(Counter& cnt, Poco::DateTime& dt) const;

protected:

	const std::string& connStr;
};

