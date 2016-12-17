/**
 * \file
 * \brief board::lowLevelInitialization() implementation for NUCLEO-F091RC
 *
 * \author Copyright (C) 2016 Kamil Szczygiel http://www.distortec.com http://www.freddiechopin.info
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "distortos/board/lowLevelInitialization.hpp"

#include "distortos/chip/CMSIS-proxy.h"

namespace distortos
{

namespace board
{

/*---------------------------------------------------------------------------------------------------------------------+
| global functions
+---------------------------------------------------------------------------------------------------------------------*/

void lowLevelInitialization()
{
	RCC->IOPENR |=
#if defined(CONFIG_BOARD_LEDS_ENABLE) || defined(CONFIG_BOARD_SPIS_ENABLE)
			RCC_IOPENR_GPIOAEN |
#endif	// defined(CONFIG_BOARD_LEDS_ENABLE) || defined(CONFIG_BOARD_SPIS_ENABLE)
#if defined(CONFIG_BOARD_BUTTONS_ENABLES)
			RCC_IOPENR_GPIOCEN |
#endif	// defined(CONFIG_BOARD_BUTTONS_ENABLES)
			0;
}

}	// namespace board

}	// namespace distortos
