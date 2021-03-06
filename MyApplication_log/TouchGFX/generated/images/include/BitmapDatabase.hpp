// Generated by imageconverter. Please, do not edit!

#ifndef TOUCHGFX_BITMAPDATABASE_HPP
#define TOUCHGFX_BITMAPDATABASE_HPP

#include <touchgfx/hal/Types.hpp>
#include <touchgfx/Bitmap.hpp>

const uint16_t BITMAP_BLUE_BUTTONS_ROUND_EDGE_SMALL_ID = 0;
const uint16_t BITMAP_BLUE_BUTTONS_ROUND_EDGE_SMALL_PRESSED_ID = 1;
const uint16_t BITMAP_DARK_BACKGROUNDS_MAIN_BG_320X240PX_ID = 2;
const uint16_t BITMAP_DARK_BACKGROUNDS_MAIN_BG_480X272PX_ID = 3;
const uint16_t BITMAP_DATE_PICKER_BACKGROUND_ID = 4;
const uint16_t BITMAP_DATE_PICKER_BAR_ID = 5;
const uint16_t BITMAP_DATE_PICKER_SHADOW_BOTTOM_ID = 6;
const uint16_t BITMAP_DATE_PICKER_SHADOW_TOP_ID = 7;
const uint16_t BITMAP_KEYBOARD_ID = 8;

namespace BitmapDatabase
{
const touchgfx::Bitmap::BitmapData* getInstance();
uint16_t getInstanceSize();
} // namespace BitmapDatabase

#endif // TOUCHGFX_BITMAPDATABASE_HPP
