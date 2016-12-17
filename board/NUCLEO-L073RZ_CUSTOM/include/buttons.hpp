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

#ifndef SOURCE_BOARD_STM32_STM32L0_NUCLEO_L073RZ_CUSTOM_INCLUDE_DISTORTOS_BOARD_BUTTONS_HPP_
#define SOURCE_BOARD_STM32_STM32L0_NUCLEO_L073RZ_CUSTOM_INCLUDE_DISTORTOS_BOARD_BUTTONS_HPP_

#include "distortos/chip/STM32-GPIOv2.hpp"

#include <array>

namespace distortos
{

#ifdef CONFIG_BOARD_BUTTONS_ENABLE

namespace chip
{

class ChipInputPin;

}	// namespace chip

#endif	// def CONFIG_BOARD_BUTTONS_ENABLE

namespace board
{

/// total number of buttons on the board
constexpr size_t totalButtons {CONFIG_BOARD_TOTAL_BUTTONS};

/*---------------------------------------------------------------------------------------------------------------------+
| button indexes
+---------------------------------------------------------------------------------------------------------------------*/

/// index of B1 button
constexpr size_t b1ButtonIndex {0};

/*---------------------------------------------------------------------------------------------------------------------+
| indexed access to pin identifiers
+---------------------------------------------------------------------------------------------------------------------*/

/// array with pin identifiers of all buttons
constexpr std::array<chip::Pin, totalButtons> buttonPins
{
		chip::Pin::pa5,
};

#ifdef CONFIG_BOARD_BUTTONS_ENABLE

/*---------------------------------------------------------------------------------------------------------------------+
| indexed access to button objects
+---------------------------------------------------------------------------------------------------------------------*/

/// array with all button objects
extern const chip::ChipInputPin buttons[totalButtons];

#endif	// def CONFIG_BOARD_BUTTONS_ENABLE

}	// namespace board

}	// namespace distortos

#endif	// SOURCE_BOARD_STM32_STM32L0_NUCLEO_L073RZ_CUSTOM_INCLUDE_DISTORTOS_BOARD_BUTTONS_HPP_