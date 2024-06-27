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

#include "../ProtocolExchange.h"

class CC301_1 : public ProtocolExchange
{
public:

	using ProtocolExchange::ProtocolExchange;   // подключаем конструктор базового класса

	Poco::DateTime readDateTime() const override;

protected:

	uint16_t calculateCRC(const uint8_t array[], int arrSize) const;

	uint16_t exchange(uint8_t answer[], int maxAnswerSize, const uint8_t messsage[], int messageSize) const;

private:

	static const uint8_t tblCRChi[256];
	static const uint8_t tblCRCho[256];

	const uint8_t COMM_COUNT_ATTEMPT = 5; // количество попыток получения данных
	const uint8_t COMM_DELAY_ATTEMPT = 3; // время ожидания в секундах между попытками
};
