// 4.18.1 0x7a875196
// Generated by imageconverter. Please, do not edit!

#include <BitmapDatabase.hpp>
#include <touchgfx/Bitmap.hpp>

extern const unsigned char image_blue_buttons_round_edge_small[]; // BITMAP_BLUE_BUTTONS_ROUND_EDGE_SMALL_ID = 0, Size: 170x60 pixels
extern const unsigned char image_blue_buttons_round_edge_small_pressed[]; // BITMAP_BLUE_BUTTONS_ROUND_EDGE_SMALL_PRESSED_ID = 1, Size: 170x60 pixels
extern const unsigned char image_dark_backgrounds_main_bg_320x240px[]; // BITMAP_DARK_BACKGROUNDS_MAIN_BG_320X240PX_ID = 2, Size: 320x240 pixels
extern const unsigned char image_dark_backgrounds_main_bg_480x272px[]; // BITMAP_DARK_BACKGROUNDS_MAIN_BG_480X272PX_ID = 3, Size: 480x272 pixels
extern const unsigned char image_date_picker_background[]; // BITMAP_DATE_PICKER_BACKGROUND_ID = 4, Size: 600x220 pixels
extern const unsigned char image_date_picker_bar[]; // BITMAP_DATE_PICKER_BAR_ID = 5, Size: 584x80 pixels
extern const unsigned char image_date_picker_shadow_bottom[]; // BITMAP_DATE_PICKER_SHADOW_BOTTOM_ID = 6, Size: 584x40 pixels
extern const unsigned char image_date_picker_shadow_top[]; // BITMAP_DATE_PICKER_SHADOW_TOP_ID = 7, Size: 584x40 pixels
extern const unsigned char image_keyboard[]; // BITMAP_KEYBOARD_ID = 8, Size: 24x24 pixels

const touchgfx::Bitmap::BitmapData bitmap_database[] = {
    { image_blue_buttons_round_edge_small, 0, 170, 60, 11, 4, 148, ((uint8_t)touchgfx::Bitmap::ARGB8888) >> 3, 50, ((uint8_t)touchgfx::Bitmap::ARGB8888) & 0x7 },
    { image_blue_buttons_round_edge_small_pressed, 0, 170, 60, 11, 4, 148, ((uint8_t)touchgfx::Bitmap::ARGB8888) >> 3, 50, ((uint8_t)touchgfx::Bitmap::ARGB8888) & 0x7 },
    { image_dark_backgrounds_main_bg_320x240px, 0, 320, 240, 0, 0, 320, ((uint8_t)touchgfx::Bitmap::RGB565) >> 3, 240, ((uint8_t)touchgfx::Bitmap::RGB565) & 0x7 },
    { image_dark_backgrounds_main_bg_480x272px, 0, 480, 272, 0, 0, 480, ((uint8_t)touchgfx::Bitmap::RGB565) >> 3, 272, ((uint8_t)touchgfx::Bitmap::RGB565) & 0x7 },
    { image_date_picker_background, 0, 600, 220, 0, 0, 600, ((uint8_t)touchgfx::Bitmap::RGB565) >> 3, 220, ((uint8_t)touchgfx::Bitmap::RGB565) & 0x7 },
    { image_date_picker_bar, 0, 584, 80, 0, 0, 584, ((uint8_t)touchgfx::Bitmap::ARGB8888) >> 3, 57, ((uint8_t)touchgfx::Bitmap::ARGB8888) & 0x7 },
    { image_date_picker_shadow_bottom, 0, 584, 40, 0, 0, 0, ((uint8_t)touchgfx::Bitmap::ARGB8888) >> 3, 0, ((uint8_t)touchgfx::Bitmap::ARGB8888) & 0x7 },
    { image_date_picker_shadow_top, 0, 584, 40, 0, 0, 0, ((uint8_t)touchgfx::Bitmap::ARGB8888) >> 3, 0, ((uint8_t)touchgfx::Bitmap::ARGB8888) & 0x7 },
    { image_keyboard, 0, 24, 24, 0, 0, 0, ((uint8_t)touchgfx::Bitmap::ARGB8888) >> 3, 0, ((uint8_t)touchgfx::Bitmap::ARGB8888) & 0x7 }
};

namespace BitmapDatabase
{
const touchgfx::Bitmap::BitmapData* getInstance()
{
    return bitmap_database;
}

uint16_t getInstanceSize()
{
    return (uint16_t)(sizeof(bitmap_database) / sizeof(touchgfx::Bitmap::BitmapData));
}
} // namespace BitmapDatabase
