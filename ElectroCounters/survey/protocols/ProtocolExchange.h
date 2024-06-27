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

class ProtocolExchange
{
public:
	ProtocolExchange(const Counter &counter) : counter(counter)
	{
	}
	virtual ~ProtocolExchange()
	{
	}

	virtual Poco::DateTime readDateTime() const = 0;

protected:

	const Counter &counter;
};
