/*
 * LPS22HB.c
 *
 *  Created on: Nov 8, 2026
 *      Author: filip
 */


#include "LPS22HB.h"

static uint8_t (* lps_read)(uint8_t dev, uint8_t reg, uint8_t *data, uint8_t len) = 0;
static uint8_t (* lps_write)(uint8_t dev, uint8_t reg, uint8_t *data, uint8_t len) = 0;

void lps22hb_register_callbacks(void *read_fn, void *write_fn)
{
	if(read_fn != 0)
	{
		lps_read = read_fn;
	}

	if(write_fn != 0)
	{
		lps_write = write_fn;
	}
}
