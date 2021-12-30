#include <gui/common/ChannelInfo.hpp>
#include <touchgfx/hal/Types.hpp>
#include <touchgfx/Unicode.hpp>

#ifdef SIMULATOR
const char gas_formulas_list[GAS_SIZE][16] =
{
	"unknown",
	"CH4",
	"C2H6",
	"C3H8",
	"C4H10",
	"C2H5OH",
};

const char gas_names_list[GAS_SIZE][16] =
{
	"unknown",
	"methane",
	"ethane",
	"propane",
	"butane",
	"ethanol"
};

const char units_list[NUMBER_OF_LANGUAGES][UNITS_SIZE][16] =
{
	{
	"unknown",
	"%LEL" ,
	"ppm" ,
	"mg/m3" ,
	"%vol"
	},
	{
	"unknown",
	"haha",
	"ppm",//{0x0025, 0x041d, 0x041a, 0x041f, 0x0420}
	"haha",//{0x043c, 0x0433, 0x002f, 0x043c, 0x0033},
	"haha"//{0x0025, 0x043e, 0x0431}
	}
};

#endif
