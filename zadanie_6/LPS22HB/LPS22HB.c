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

uint8_t lps22hb_read(uint8_t reg, uint8_t *data, uint8_t len)
{
	if(lps_read == 0) return 0;

	return lps_read(LPS22HB_I2C_ADDRESS, reg, data, len);
}

uint8_t lps22hb_write(uint8_t reg, uint8_t *data, uint8_t len)
{
	if(lps_write == 0) return 0;

	return lps_write(LPS22HB_I2C_ADDRESS, reg, data, len);
}

uint8_t lps22hb_init(void)
{
	uint8_t id = 0;
	uint8_t config = LPS22HB_CTRL1_ODR_10HZ;

	if(!lps22hb_read(LPS22HB_WHO_AM_I_ADDRESS, &id, 1)) return 0;
	if(id != LPS22HB_WHO_AM_I_VALUE) return 0;

	return lps22hb_write(LPS22HB_CTRL_REG1, &config, 1);
}

uint8_t get_pressure(*pressure)
{
	uint8_t buf[3];
	if(!lps22hp_read(LPS22HB_PRESS_OUT_XL, buf, 3)) return 0;

	uint32_t p_out = (uint32_t)(buf[2] << 16 | buf[1] << 8 | buf[0]);
	*pressure = p_out / LPS22HP_PRESSURE_SENSITIVITY;
	return 1;
}
