/*
 * ChannelInfo.hpp
 *
 *  Created on: May 15, 2021
 *      Author: me
 */

#ifndef APPLICATION_USER_GUI_CHANNELINFO_HPP_
#define APPLICATION_USER_GUI_CHANNELINFO_HPP_

#include <touchgfx/hal/types.hpp>
#include <texts/TextKeysAndLanguages.hpp>

#ifdef SIMULATOR

#define STATUS_GET_TYPE(STATUS) ((STATUS >> 12) & 0xF)
#define STATUS_GET_LOOP_STATE(STATUS) ((STATUS >> 8) & 0xF)
#define STATUS_GET_THLD(STATUS) ((STATUS >> 4) & 0xF)
#define STATUS_GET_ERROR(STATUS) ((STATUS >> 0) & 0xF)
#define STATUS_SET(TYPE, STATE, THLD, ERROR) (uint16_t) ( (TYPE << 12) | (STATE << 12) | (THLD << 4) | (ERROR << 0) )
#define STATUS_SET_CH_TYPE(STATUS, TYPE) (uint16_t) (STATUS &=~(0xF << 12) ); (STATUS |= (TYPE << 12) )
#define STATUS_SET_LOOP_STATE(STATUS, STATE) (uint16_t) (STATUS &=~(0xF << 8) ); (STATUS |= (STATE << 8) )
#define STATUS_SET_THLD(STATUS, THLD) (uint16_t) (STATUS &=~(0xF << 4) ); (STATUS |= (THLD << 4) )
#define STATUS_SET_ERROR(STATUS, ERROR) (uint16_t) (STATUS &=~(0xF << 0) ); (STATUS |= (MODE << 0) )

enum status_channel_type
{
	CH_TYPE_UNKNOWN,
	CH_TYPE_MV_LOOP,
	CH_TYPE_MV_CAT,
	CH_TYPE_MR,
	CH_TYPE_SIZE
};

enum status_loop_state
{
	LOOP_STATE_UNKNOWN,
	LOOP_STATE_INITIALIZATION,
	LOOP_STATE_CURRENT_IN_RANGE,
	LOOP_STATE_CALIBRATION_ZERO,
	LOOP_STATE_CALIBRATION_CONC,
	LOOP_STATE_CALIBRATION_CURRENT_4,
	LOOP_STATE_CALIBRATION_CURRENT_20,
	LOOP_STATE_CONCENTRATION_EXCEEDED,
	LOOP_STATE_NO_CURRENT,
	LOOP_STATE_SIZE
};

enum status_threshold_state
{
	THLD_UNKNOWN,
	THLD_NONE,
	THLD_1_EXCEEDED,
	THLD_2_EXCEEDED,
	THLD_3_EXCEEDED,
	THLD_SIZE
};

enum status_error_code
{
	ERROR_SIZE
};

#define SETTINGS_GET_GAS(SETTINGS) ((SETTINGS >> 8) & 0xFF)
#define SETTINGS_GET_UNITS(SETTINGS) ((SETTINGS >> 4) & 0xF)
#define SETTINGS_GET_MULTIPLIER(SETTINGS) ((SETTINGS >> 2) & 0x3)
#define SETTINGS_SET_GAS(SETTINGS, GAS) (uint16_t) (SETTINGS &=~(0xFF << 8) ); (SETTINGS |= (GAS << 8) )
#define SETTINGS_SET_UNITS(SETTINGS, UNITS) (uint16_t) (SETTINGS &=~(0xF << 4) ); (SETTINGS |= (UNITS << 4) )
#define SETTINGS_SET_MULTIPLIER(SETTINGS, MULTIPLIER) (uint16_t) (SETTINGS &=~(0x3 << 4) ); (SETTINGS |= (MULTIPLIER << 2) )
#define SETTINGS_SET(GAS, UNITS, MULTIPLIER) (uint16_t) ( (GAS << 8) | (UNITS << 4) | (MULTIPLIER << 2) )

enum gas_decoder
{
	GAS_UNKNOWN,
	GAS_CH4,
	GAS_C2H6,
	GAS_C3H8,
	GAS_C4H10,
	GAS_C2H5OH,
	GAS_SIZE
};

enum units_decoder
{
	UNITS_UNKNOWN,
	UNITS_LEL,
	UNITS_PPM,
	UNITS_MGM3,
	UNITS_VOLUME_FRACTION,
	UNITS_SIZE
};

enum multiplier_decoder
{
	MULTIPLIER_SIZE
};

typedef struct
{
	uint8_t ch_on;
	uint8_t loop_state;
	uint8_t thld_state;
	uint8_t error_state;
	uint8_t gas;
	uint8_t units;
	uint8_t multiplier;
	uint8_t ch_type;
	float concentration;
} BriefInfoTypeDef;

typedef struct
{
	uint8_t ch_on;
	uint8_t loop_state;
	uint8_t thld_state;
	uint8_t error_state;
	uint8_t gas;
	uint8_t units;
	uint8_t multiplier;
	uint8_t ch_type;
	float concentration;

	float threshold_1;
	float threshold_2;
	float threshold_3;
	float full_scale;
	float hysteresis;
	char buf_tag[24];
} DetailedInfoTypeDef;

extern const char gas_formulas_list[GAS_SIZE][16];
extern const char gas_names_list[GAS_SIZE][16];
extern const char units_list[NUMBER_OF_LANGUAGES][UNITS_SIZE][16];

#endif


#endif /* APPLICATION_USER_GUI_CHANNELINFO_HPP_ */
