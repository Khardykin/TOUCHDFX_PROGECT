/*
 * UserUtils.hpp
 *
 *  Created on: Nov 24, 2021
 *      Author: me
 */

#ifndef GUI_INCLUDE_GUI_COMMON_USERUTILS_HPP_
#define GUI_INCLUDE_GUI_COMMON_USERUTILS_HPP_

#include <cstring>
#include <cinttypes>
#include <touchgfx/hal/Types.hpp>
#include <touchgfx/Unicode.hpp>

using namespace touchgfx;

class UserUtils
{
public:
	UserUtils();
    virtual ~UserUtils() {}

    virtual void gasNameFromFormula(Unicode::UnicodeChar *formula, Unicode::UnicodeChar *name);
    virtual void getBufferToDisplay(Unicode::UnicodeChar* buffer, float value, uint8_t units);

protected:

};

#endif /* GUI_INCLUDE_GUI_COMMON_USERUTILS_HPP_ */
