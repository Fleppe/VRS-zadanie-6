/*
 * HTS221.c
 *
 *  Created on: Nov 8, 2026
 *      Author: filip
 */


#include "HTS221.h"

static uint8_t (* hts_read)(uint8_t dev, uint8_t reg, uint8_t *data, uint8_t len) = 0;
static uint8_t (* hts_write)(uint8_t dev, uint8_t reg, uint8_t *data, uint8_t len) = 0;

void hts221_register_callbacks(void *read_fn, void *write_fn)
{
	if(read_fn != 0)
	{
		hts_read = read_fn;
	}

	if(write_fn != 0)
	{
		hts_write = write_fn;
	}
}
