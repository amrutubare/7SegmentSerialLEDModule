/**
 * \file
 * \brief SpiLed7SegmentModule example application
 *
 * \author Copyright (C) 2016 - 2017 Cezary Gapinski cezary.gapinski@gmail.com
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "distortos/distortosConfiguration.h"

#include "distortos/chip/ChipOutputPin.hpp"

#include "distortos/devices/communication/SpiMaster.hpp"
#include "distortos/chip/spis.hpp"
#include "distortos/chip/ChipSpiMasterLowLevel.hpp"

#include "distortos/StaticThread.hpp"
#include "distortos/ThisThread.hpp"

#include "distortos/board/spi.hpp"
#include "../devices/SpiLed7SegmentModule/SpiLed7SegmentModule.hpp"

namespace
{
/*---------------------------------------------------------------------------------------------------------------------+
| local functions
+---------------------------------------------------------------------------------------------------------------------*/

/**
 * \brief incrementing function
 *
 * Incrementing value for SpiLed7SegmentModule driver with \a periodMs.
 *
 * \param [in] ledDevice is a reference to external_devices::Led7SegmentModule object which value will be changed
 * \param [in] periodMs is a full (on -> off -> on) period of toggling, milliseconds
 */

static void incrementFunction(external_devices::SpiLed7SegmentModule& ledDevice, const std::chrono::milliseconds periodMs)
{
	uint16_t value = 0;

	while (1)
	{
		ledDevice.write(value);
		value++;
		distortos::ThisThread::sleepFor(periodMs);
	}
}

} /// namespace

/**
 * \brief Main code block of SpiLed7SegmentModule application
 *
 * This example application tries to demonstrate the concept of user 4 digits 7 segments LED driver
 * based on 74HC595 driver:
 * - creating and starting them,
 * - incrementing and writing value to this device from other thread in one second period
 * - joining them.
 *
 * To run this example SPI driver has to be enabled. The SpiLed7SegmentModule driver using a one internal thread
 * to refresh value on digits.
 *
 * \return doesn't return
 */

int main()
{
#if defined(CONFIG_CHIP_STM32_SPIV1_SPI1_ENABLE) && defined(CONFIG_BOARD_NUCLEO_L073RZ_CUSTOM)
	distortos::devices::SpiMaster spiMaster(distortos::chip::spi1);
	external_devices::SpiLed7SegmentModule ledDevice(spiMaster, distortos::board::spi1pins.getCs());
	// create and immediately start static thread with 1024 bytes of stack, low priority (1), incrementFunction() will
	// get segment digital display by reference and period by value
	auto incrementThread = distortos::makeAndStartStaticThread<1024>(2, incrementFunction,
			std::ref(ledDevice), std::chrono::milliseconds{1000});

	incrementThread.join();
#endif // defined(CONFIG_CHIP_STM32_SPIV3_SPI1_ENABLE) && defined(CONFIG_BOARD_NUCLEO_L073RZ)
	return 0;
}
