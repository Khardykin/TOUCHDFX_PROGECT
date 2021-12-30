/*
 * mb_regs_decoder.c
 *
 *  Created on: Dec 16, 2021
 *      Author: me
 */
#include "mb_regs_decoder.h"

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

const char units_list[UNITS_SIZE][16] =
{
	"unknown",
	"% LEL",
	"ppm",
	"mgm3",
	"%"
};
