/**
 * \file
 * \brief SpiLed7SegmentModule class implementation
 *
 * \author Copyright (C) 2016 - 2017 Cezary Gapinski cezary.gapinski@gmail.com
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "SpiLed7SegmentModule.hpp"

#include "distortos/devices/communication/SpiMasterOperation.hpp"

#include "distortos/assert.h"
#include "distortos/ThisThread.hpp"

#include "estd/ScopeGuard.hpp"

#include <tuple>
#include <array>

#include <cerrno>

namespace external_devices
{

/*---------------------------------------------------------------------------------------------------------------------+
| public functions
+---------------------------------------------------------------------------------------------------------------------*/

SpiLed7SegmentModule::SpiLed7SegmentModule(distortos::devices::SpiMaster& spiMaster, distortos::devices::OutputPin& slaveSelectPin,
		const bool mode3, const uint32_t maxClockFrequency) :
				spiDevice_{spiMaster, slaveSelectPin, mode3 == false ? distortos::devices::SpiMode::_0 : distortos::devices::SpiMode::_3,
						maxClockFrequency, 16, false}, decodedDigitsBuffer{},
				refhreshDisplayThread{distortos::makeAndStartStaticThread<1024>(1, ledBlinkerFunction, this)},
				finishThread{}
{
	open();
}

void SpiLed7SegmentModule::ledBlinkerFunction(SpiLed7SegmentModule *ledDevice)
{
	static uint16_t spiBuffer = 0;
	static uint8_t index = 0;

	distortos::devices::SpiMasterOperation operation {distortos::devices::SpiMasterOperation::Transfer{&spiBuffer, nullptr, sizeof(spiBuffer)}};

	while (1)
	{
		if (ledDevice->isFinishThread())
			break;

		ledDevice->mutex_.lock();
		spiBuffer = ledDevice->decodedDigitsBuffer[index];
		ledDevice->mutex_.unlock();
		index++;
		index %= 4;
		ledDevice->spiDevice_.executeTransaction(distortos::devices::SpiMasterOperationRange{operation}).first;
	}
}

SpiLed7SegmentModule::~SpiLed7SegmentModule()
{
	finishThread = true;
	refhreshDisplayThread.join();
}

int SpiLed7SegmentModule::close()
{
	return spiDevice_.close();
}

bool SpiLed7SegmentModule::lock()
{
	return spiDevice_.lock();
}

int SpiLed7SegmentModule::open()
{
	return spiDevice_.open();
}

int SpiLed7SegmentModule::write(uint16_t value)
{
	mutex_.lock();
	const auto mutexScopeGuard = estd::makeScopeGuard(
			[this]()
			{
				mutex_.unlock();
			});

	numberToDigitsDisplay(value, decodedDigitsBuffer);

	return 0;
}

bool SpiLed7SegmentModule::isFinishThread()
{
	return finishThread;
}

void SpiLed7SegmentModule::numberToDigitsDisplay(uint16_t number, SpiDecodedDigitsBuffer& output)
{
	std::array<uint8_t, 10> displ_decoded_digits = {
		0xC0, //0
		0xF9, //1
		0xA4, //2
		0xB0, //3
		0x99, //4
		0x92, //5
		0x82, //6
		0xF8, //7
		0x80, //8
		0x90, //9
	};

	std::array<uint8_t, 4> part_chooser = {
		0x01, 0x02, 0x04, 0x08,
	};

	for(uint8_t i = 0; i < 4; i++)
	{
		output[i] = part_chooser[i];
		output[i] |= displ_decoded_digits[number % 10] << 8;

		number /= 10;
	}
}

}
