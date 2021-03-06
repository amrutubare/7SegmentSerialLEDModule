#
# file: Rules.mk
#
# author: Copyright (C) 2016 Kamil Szczygiel http://www.distortec.com http://www.freddiechopin.info
#
# This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
# distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
#

#-----------------------------------------------------------------------------------------------------------------------
# subdirectories
#-----------------------------------------------------------------------------------------------------------------------

SUBDIRECTORIES += SpiLed7SegmentModule

#-----------------------------------------------------------------------------------------------------------------------
# compilation flags
#-----------------------------------------------------------------------------------------------------------------------

CXXFLAGS_$(d) := $(CXXFLAGS_$(d)) $(STANDARD_INCLUDES)
CXXFLAGS_$(d) := $(CXXFLAGS_$(d)) -I$(d)SpiLed7SegmentModule

#-----------------------------------------------------------------------------------------------------------------------
# standard footer
#-----------------------------------------------------------------------------------------------------------------------

include $(DISTORTOS_PATH)footer.mk
