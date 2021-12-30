/*
 * UserUtils.cpp
 *
 *  Created on: Nov 24, 2021
 *      Author: me
 */
#include <gui/common/UserUtils.hpp>
#include <touchgfx/Unicode.hpp>
//#include <gui/screenchannelconfig_screen/ScreenChannelConfigView.hpp>
#include <gui/common/ChannelInfo.hpp>

#ifndef SIMULATOR
#include <mb_regs_decoder.h>
#include "registers_map.h"
#endif

UserUtils::UserUtils()
{

}

void UserUtils::gasNameFromFormula(Unicode::UnicodeChar *formula, Unicode::UnicodeChar *name)
{
	 Unicode::UnicodeChar ch4[10] = {0}, c2h6[10] = {0}, c3h8[10] = {0}, c4h10[10] = {0}, c2h5oh[10] = {0};

	 Unicode::snprintf(ch4, 10,  "CH4");
	 Unicode::snprintf(c2h6, 10,  "C2H6");
	 Unicode::snprintf(c3h8, 10,  "C3H8");
	 Unicode::snprintf(c4h10, 10,  "C4H10");
	 Unicode::snprintf(c2h5oh, 10,  "C2H5OH");

	if (!Unicode::strncmp_ignore_whitespace(ch4, formula, 24))
			Unicode::snprintf(name, 24, "Methane");
	else if (!Unicode::strncmp_ignore_whitespace(c2h6, formula, 10))
			Unicode::snprintf(name, 24, "Ethane");
	else if (!Unicode::strncmp_ignore_whitespace(c3h8, formula, 10))
			Unicode::snprintf(name, 24, "Propane");
	else if (!Unicode::strncmp_ignore_whitespace(c4h10, formula, 10))
			Unicode::snprintf(name, 24, "Butane");
	else if (!Unicode::strncmp_ignore_whitespace(c2h5oh, formula, 10))
			Unicode::snprintf(name, 24, "Alcohol");
	else Unicode::snprintf(name, 24, "Unknown");
}

void UserUtils::getBufferToDisplay(Unicode::UnicodeChar* buffer, float value, uint8_t units)
{
	//int size = Unicode::strlen(buffer);

	if (units == UNITS_VOLUME_FRACTION)
		Unicode::snprintfFloat(buffer, 6, "%.2f", value);
	else
		Unicode::snprintf(buffer, 6, "%d", (int)value);
}
