/* DO NOT EDIT THIS FILE */
/* This file is autogenerated by the text-database code generator */

#include <stdarg.h>
#include <touchgfx/TextProvider.hpp>
#include <touchgfx/Texts.hpp>
#include <touchgfx/TypedText.hpp>
#include <touchgfx/Unicode.hpp>
#include <touchgfx/hal/HAL.hpp>
#include <touchgfx/lcd/LCD.hpp>
#include <texts/TypedTextDatabase.hpp>

uint16_t touchgfx::Font::getStringWidth(const touchgfx::Unicode::UnicodeChar* text, ...) const
{
    va_list pArg;
    va_start(pArg, text);
    uint16_t width = getStringWidthRTL(TEXT_DIRECTION_LTR, text, pArg);
    va_end(pArg);
    return width;
}

uint16_t touchgfx::Font::getStringWidth(touchgfx::TextDirection textDirection, const touchgfx::Unicode::UnicodeChar* text, ...) const
{
    va_list pArg;
    va_start(pArg, text);
    uint16_t width = getStringWidthRTL(textDirection, text, pArg);
    va_end(pArg);
    return width;
}

touchgfx::Unicode::UnicodeChar touchgfx::TextProvider::getNextLigature(TextDirection direction)
{
    nextCharacters.replaceAt0(unicodeConverter(direction));
    if (fontGsubTable && nextCharacters.peekChar())
    {
        substituteGlyphs();
        if (nextCharacters.peekChar(1) == 0x093F) // Hindi I-matra
        {
            nextCharacters.replaceAt1(nextCharacters.peekChar());
            nextCharacters.replaceAt0(0x093F);
        }
    }
    return getNextChar();
}

void touchgfx::TextProvider::initializeInternal()
{
    fillInputBuffer();
    unicodeConverterInit();
}

void touchgfx::LCD::drawString(touchgfx::Rect widgetArea, const touchgfx::Rect& invalidatedArea, const touchgfx::LCD::StringVisuals& stringVisuals, const touchgfx::Unicode::UnicodeChar* format, ...)
{
    va_list pArg;
    va_start(pArg, format);
    drawStringRTL(widgetArea, invalidatedArea, stringVisuals, format, pArg);
    va_end(pArg);
}

//Default typed text database
extern const touchgfx::TypedText::TypedTextData* const typedTextDatabaseArray[];

TEXT_LOCATION_FLASH_PRAGMA
KEEP extern const touchgfx::Unicode::UnicodeChar texts_all_languages[] TEXT_LOCATION_FLASH_ATTRIBUTE = {
    0x421, 0x43e, 0x445, 0x440, 0x430, 0x43d, 0x438, 0x442, 0x44c, 0x20, 0xa, 0x43d, 0x430, 0x441, 0x442, 0x440, 0x43e, 0x439, 0x43a, 0x438, 0x3f, 0x0, // @0 "????????? ???????????"
    0x421, 0x43e, 0x445, 0x440, 0x430, 0x43d, 0x438, 0x442, 0x44c, 0x20, 0x43d, 0x430, 0x441, 0x442, 0x440, 0x43e, 0x439, 0x43a, 0x438, 0x3f, 0x0, // @22 "????????? ??????????"
    0x30, 0x31, 0x2d, 0x30, 0x31, 0x2d, 0x31, 0x39, 0x30, 0x30, 0x20, 0x31, 0x30, 0x3a, 0x31, 0x30, 0x0, // @43 "01-01-1900 10:10"
    0x424, 0x438, 0x43b, 0x44c, 0x442, 0x440, 0x20, 0x43f, 0x43e, 0x20, 0x434, 0x430, 0x442, 0x435, 0x0, // @60 "?????? ?? ????"
    0x43, 0x41, 0x50, 0x53, 0x20, 0xa, 0x4c, 0x4f, 0x43, 0x4b, 0xa, 0xa, 0x0, // @75 "CAPS ?LOCK??"
    0x427, 0x442, 0x435, 0x43d, 0x438, 0x435, 0x20, 0x43b, 0x43e, 0x433, 0x43e, 0x432, 0x0, // @88 "?????? ?????"
    0x44, 0x65, 0x6c, 0x65, 0x74, 0x65, 0x20, 0x61, 0x6c, 0x6c, 0x0, // @101 "Delete all"
    0x42, 0x61, 0x63, 0x6b, 0x73, 0x70, 0x61, 0x63, 0x65, 0x0, // @112 "Backspace"
    0x4e, 0x65, 0x77, 0x20, 0x54, 0x65, 0x78, 0x74, 0x0, // @122 "New Text"
    0x2, 0x0, // @131 "<>"
    0x43, 0x34, 0x48, 0x31, 0x32, 0x4f, 0x48, 0x0, // @133 "C4H12OH"
    0x41f, 0x43e, 0x440, 0x43e, 0x433, 0x20, 0x31, 0x0, // @141 "????? 1"
    0x45, 0x4e, 0x54, 0x45, 0x52, 0xa, 0x0, // @149 "ENTER?"
    0x43, 0x4c, 0x4f, 0x53, 0x45, 0x0, // @156 "CLOSE"
    0x43, 0x6c, 0x6f, 0x73, 0x65, 0x0, // @162 "Close"
    0x45, 0x4e, 0x54, 0x45, 0x52, 0x0, // @168 "ENTER"
    0x41e, 0x431, 0x440, 0x44b, 0x432, 0x0, // @174 "?????"
    0x41f, 0x435, 0x442, 0x43b, 0x44f, 0x0, // @180 "?????"
    0x45, 0x78, 0x69, 0x74, 0x0, // @186 "Exit"
    0x31, 0x30, 0x30, 0x0, // @191 "100"
    0x41, 0x42, 0x43, 0x0, // @195 "ABC"
    0x45, 0x72, 0x72, 0x0, // @199 "Err"
    0x4c, 0x45, 0x4c, 0x0, // @203 "LEL"
    0x41d, 0x435, 0x442, 0x0, // @207 "???"
    0x424, 0x73, 0x64, 0x0, // @211 "?sd"
    0x31, 0x35, 0x0, // @215 "15"
    0x41, 0x53, 0x0, // @218 "AS"
    0x45, 0x4e, 0x0, // @221 "EN"
    0x4f, 0x6b, 0x0, // @224 "Ok"
    0x414, 0x430, 0x0, // @227 "??"
    0x32, 0x0, // @230 "2"
    0x33, 0x0, // @232 "3"
    0x34, 0x0, // @234 "4"
    0x3c, 0x0, // @236 "<"
    0x3e, 0x0, // @238 ">"
    0x51, 0x0 // @240 "Q"
};
TEXT_LOCATION_FLASH_PRAGMA
KEEP extern uint32_t const indicesGb[] TEXT_LOCATION_FLASH_ATTRIBUTE;

//array holding dynamically installed languages
struct TranslationHeader
{
    uint32_t offset_to_texts;
    uint32_t offset_to_indices;
    uint32_t offset_to_typedtext;
};
static const TranslationHeader* languagesArray[1] = { 0 };

//Compiled and linked in languages
static const uint32_t* const staticLanguageIndices[] = {
    indicesGb
};

touchgfx::LanguageId touchgfx::Texts::currentLanguage = static_cast<touchgfx::LanguageId>(0);
static const touchgfx::Unicode::UnicodeChar* currentLanguagePtr = 0;
static const uint32_t* currentLanguageIndices = 0;

void touchgfx::Texts::setLanguage(touchgfx::LanguageId id)
{
    const touchgfx::TypedText::TypedTextData* currentLanguageTypedText = 0;
    if (id < 1)
    {
        if (languagesArray[id] != 0)
        {
            // Dynamic translation is added
            const TranslationHeader* translation = languagesArray[id];
            currentLanguagePtr = (const touchgfx::Unicode::UnicodeChar*)(((const uint8_t*)translation) + translation->offset_to_texts);
            currentLanguageIndices = (const uint32_t*)(((const uint8_t*)translation) + translation->offset_to_indices);
            currentLanguageTypedText = (const touchgfx::TypedText::TypedTextData*)(((const uint8_t*)translation) + translation->offset_to_typedtext);
        }
        else
        {
            // Compiled and linked in languages
            currentLanguagePtr = texts_all_languages;
            currentLanguageIndices = staticLanguageIndices[id];
            currentLanguageTypedText = typedTextDatabaseArray[id];
        }
    }

    if (currentLanguageTypedText)
    {
        currentLanguage = id;
        touchgfx::TypedText::registerTypedTextDatabase(currentLanguageTypedText,
                                                       TypedTextDatabase::getFonts(), TypedTextDatabase::getInstanceSize());
    }
}

void touchgfx::Texts::setTranslation(touchgfx::LanguageId id, const void* translation)
{
    languagesArray[id] = (const TranslationHeader*)translation;
}

const touchgfx::Unicode::UnicodeChar* touchgfx::Texts::getText(TypedTextId id) const
{
    return &currentLanguagePtr[currentLanguageIndices[id]];
}
