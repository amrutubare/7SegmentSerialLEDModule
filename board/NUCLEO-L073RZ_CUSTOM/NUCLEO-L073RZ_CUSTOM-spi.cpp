/**
 * \file
 * \brief Definition of SPIs for NUCLEO-L073RZ
 *
 * \author Copyright (C) 2016 Kamil Szczygiel http://www.distortec.com http://www.freddiechopin.info
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "distortos/board/spi.hpp"

#ifdef CONFIG_BOARD_SPIS_ENABLE

#include "distortos/chip/ChipOutputPin.hpp"

namespace distortos
{

namespace board
{

/*---------------------------------------------------------------------------------------------------------------------+
| global objects
+---------------------------------------------------------------------------------------------------------------------*/

SpiPins::SpiPins(distortos::chip::ChipOutputPin& cs, distortos::chip::Pin clk, chip::Pin miso, distortos::chip::Pin mosi)
: _cs{cs}
{

	chip::configureAlternateFunctionPin(clk, false, chip::PinOutputSpeed::veryHigh,
			chip::PinPull::up, chip::PinAlternateFunction::af0);
	chip::configureAlternateFunctionPin(miso, false, chip::PinOutputSpeed::veryHigh,
			chip::PinPull::up, chip::PinAlternateFunction::af0);
	chip::configureAlternateFunctionPin(mosi, false, chip::PinOutputSpeed::veryHigh,
			chip::PinPull::up, chip::PinAlternateFunction::af0);

}

distortos::chip::ChipOutputPin& SpiPins::getCs()
{
	return _cs;
}

distortos::chip::ChipOutputPin cs{chip::Pin::pa4};

distortos::board::SpiPins spi1pins(cs, distortos::chip::Pin::pa5, distortos::chip::Pin::pa11, distortos::chip::Pin::pa12);

}	// namespace board

}	// namespace distortos

#endif	// def CONFIG_BOARD_SPIS_ENABLE
