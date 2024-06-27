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

#if __has_include(<format>)
#include <format>
#else
#include <Poco/Format.h>
#endif

#include <string>


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
#ifdef __cpp_lib_format
		return std::format("Counter id {} at {}:{}", id, ip.value(), port.value());
#else
		// Code without std::format, or just #error if you only
		// want to support compilers and standard libraries with std::format
		return Poco::format("Counter id %d at %s:%d", id, ip.value(), port.value());
#endif
	}
};
