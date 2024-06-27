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

#include <Poco/Nullable.h>

#include <string>
#include <format>

struct Counter
{
	int id;
	Poco::Nullable<std::string> ip;
	Poco::Nullable<int>			port;
	Poco::Nullable<std::string> zn;
	Poco::Nullable<int>			sa;
	Poco::Nullable<std::string> protocol;

	operator std::string() const
	{
		return std::format("Counter id {} at {}:{}", id, ip.value(), port.value());
	}
};
