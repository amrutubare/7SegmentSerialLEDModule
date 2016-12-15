/**
 * \file
 * \brief SpiLed7SegmentModule class header
 *
 * \author Copyright (C) 2016 Cezary Gapinski cezary.gapinski@gmail.com
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#ifndef INCLUDE_EXTERNAL_DEVICES_LED7SEGMENTMODULE_HPP_
#define INCLUDE_EXTERNAL_DEVICES_LED7SEGMENTMODULE_HPP_

#include "distortos/devices/communication/SpiDevice.hpp"

#include "distortos/StaticThread.hpp"
#include "distortos/ThisThread.hpp"

#include "distortos/Mutex.hpp"

namespace external_devices
{

class SpiLed7SegmentModule
{
public:
	/// buffer for four decoded digits cyclically refreshed on spi driver
	using SpiDecodedDigitsBuffer = std::array<uint16_t, 4>;
	/// type for internal thread used to update value on display
	using thread_type = distortos::StaticThread<1024u, false, 0u, 0u, void (&)(SpiLed7SegmentModule*), SpiLed7SegmentModule*>;

	/**
	 * \brief SpiLed7SegmentModule's constructor
	 *
	 * \param [in] spiMaster is a reference to SPI master to which this 7 segment display is connected
	 * \param [in] slaveSelectPin is a reference to slave select pin of this 7 segment display
	 * \param [in] mode3 selects whether SPI mode 0 - CPOL == 0, CPHA == 0 - (false) or SPI mode 3 - CPOL == 1,
	 * CPHA == 1 - (true) will be used, default - SPI mode 0 (false)
	 * \param [in] maxClockFrequency is the max clock frequency supported by display, Hz, default - 16MHz
	 */

	SpiLed7SegmentModule(distortos::devices::SpiMaster& spiMaster, distortos::devices::OutputPin& slaveSelectPin,
			const bool mode3 = {}, const uint32_t maxClockFrequency = 16000000);

	~SpiLed7SegmentModule();

	static void ledBlinkerFunction(SpiLed7SegmentModule *ledDevice);

	/**
	 * \brief Wrapper for SpiDevice::lock()
	 *
	 * \note Locks may be nested.
	 *
	 * \return previous state of lock: false if this SPI EEPROM was unlocked before this call, true if it was already
	 * locked by current thread
	 */

	bool lock();

	/**
	 * \brief Writes value from 0 to 9999.
	 *
	 * \param [in] value to display from range 0 to number of digits - now equal to 4 digits
	 *
	 * \return return code (0 on success, error code otherwise)
	 */

	int write(uint16_t value);

private:

	/**
	 * \brief check if we need to stop thread for refreshing digits values
	 *
	 * \return true if thread to control display has to be finished
	 */

	bool isFinishThread();

	/**
	 * \brief Opens SpiLed7SegmentModule.
	 *
	 * Wrapper for SpiDevice::open().
	 *
	 * \return 0 on success, error code otherwise:
	 * - error codes returned by SpiDevice::open();
	 */

	int open();

	/**
	 * \brief Closes SpiLed7SegmentModule.
	 *
	 * Wrapper for SpiDevice::close().
	 *
	 * \return 0 on success, error code otherwise:
	 * - error codes returned by SpiDevice::close();
	 */

	int close();

	/**
	 * \brief Convert numeric value to display drivers code
	 *
	 * \param [in] value to display from range 0 to number of digits - now equal to 4 digits
	 * \param [out] output value decoded to display format
	 */
	void numberToDigitsDisplay(uint16_t number, SpiDecodedDigitsBuffer& output);

	/// internal SPI slave device
	distortos::devices::SpiDevice spiDevice_;

	/// mutex used to serialize access to this object
	distortos::Mutex mutex_;

	/// internal buffer for decoded numbers to driver format
	SpiDecodedDigitsBuffer decodedDigitsBuffer;

	/// type of function for thread
	thread_type refhreshDisplayThread;

	bool finishThread;
};

}

#endif	// INCLUDE_EXTERNAL_DEVICES_LED7SEGMENTMODULE_HPP_
