/**
 * \file
 * \brief Declaration of buttons for NUCLEO-L073RZ_CUSTOM
 *
 * \author Copyright (C) 2016 Cezary Gapinski cezary.gapinski@gmail.com
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef SOURCE_BOARD_STM32_STM32L0_NUCLEO_L073RZ_CUSTOM_INCLUDE_DISTORTOS_BOARD_SPIS_HPP_
#define SOURCE_BOARD_STM32_STM32L0_NUCLEO_L073RZ_CUSTOM_INCLUDE_DISTORTOS_BOARD_SPIS_HPP_

#include "distortos/chip/STM32-GPIOv2.hpp"

#include <array>

namespace distortos
{

#ifdef CONFIG_BOARD_SPIS_ENABLE

namespace chip
{

class ChipOutputPin;

}	// namespace chip

#endif	// def CONFIG_BOARD_SPIS_ENABLE

namespace board
{

class SpiPins
{
public:
	explicit SpiPins(distortos::chip::ChipOutputPin& cs, distortos::chip::Pin clk, distortos::chip::Pin miso, distortos::chip::Pin mosi);
	distortos::chip::ChipOutputPin& getCs();

private:
	distortos::chip::ChipOutputPin& _cs;
};

/// total number of buttons on the board
constexpr size_t totalSpis {CONFIG_BOARD_TOTAL_SPIS};

/*---------------------------------------------------------------------------------------------------------------------+
| button indexes
+---------------------------------------------------------------------------------------------------------------------*/

/// index of spi1 configuration
constexpr size_t spi1Index {0};

/*---------------------------------------------------------------------------------------------------------------------+
| indexed access to pin identifiers
+---------------------------------------------------------------------------------------------------------------------*/

extern distortos::board::SpiPins spi1pins;

/// array with pin identifiers of all spi Pins
constexpr std::array<SpiPins *, totalSpis> spiPins
{
	&spi1pins,
};

#ifdef CONFIG_BOARD_SPIS_ENABLE

/*---------------------------------------------------------------------------------------------------------------------+
| indexed access to spi pins objects
+---------------------------------------------------------------------------------------------------------------------*/

/// array with all spi pins objects
extern const distortos::board::SpiPins spis[totalSpis];

#endif	// def CONFIG_BOARD_SPIS_ENABLE

}	// namespace board

}	// namespace distortos

#endif	// SOURCE_BOARD_STM32_STM32L0_NUCLEO_L073RZ_CUSTOM_INCLUDE_DISTORTOS_BOARD_SPIS_HPP_
