/*
 * LPS25HB.c
 *
 *  Created on: Nov 8, 2026
 *      Author: filip
 */


#include "LPS25HB.h"

static uint8_t (* lps_read)(uint8_t dev, uint8_t reg, uint8_t *data, uint8_t len) = 0;
static uint8_t (* lps_write)(uint8_t dev, uint8_t reg, uint8_t *data, uint8_t len) = 0;

void lps25hb_register_callbacks(void *read_fn, void *write_fn)
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

uint8_t lps25hb_read(uint8_t reg, uint8_t *data, uint8_t len)
{
	if(lps_read == 0) return 0;

	if(len > 1) reg |= LPS25HB_AUTO_INCREMENT;
	return lps_read(LPS25HB_I2C_ADDRESS, reg, data, len);
}

uint8_t lps25hb_write(uint8_t reg, uint8_t *data, uint8_t len)
{
	if(lps_write == 0) return 0;

	if(len > 1) reg |= LPS25HB_AUTO_INCREMENT;
	return lps_write(LPS25HB_I2C_ADDRESS, reg, data, len);
}

uint8_t lps25hb_init(void)
{
	uint8_t id = 0;
	uint8_t config = LPS25HB_CTRL1_PD | LPS25HB_CTRL1_BDU | LPS25HB_CTRL1_ODR_12_5HZ;

	if(!lps25hb_read(LPS25HB_WHO_AM_I_ADDRESS, &id, 1)) return 0;
	if(id != LPS25HB_WHO_AM_I_VALUE) return 0;

	return lps25hb_write(LPS25HB_CTRL_REG1, &config, 1);
}

uint8_t get_pressure(float *pressure)
{
	uint8_t buf[3];
	if(!lps25hb_read(LPS25HB_PRESS_OUT_XL, buf, 3)) return 0;

	uint32_t p_out = (uint32_t)(buf[2] << 16 | buf[1] << 8 | buf[0]);
	*pressure = p_out / LPS25HB_PRESSURE_SENSITIVITY;
	return 1;
}
float calculate_altitude(float pressure, float reference_pressure)
{
	return 44330.0f * (1.0f - powf(pressure / reference_pressure, 1.0f / 5.255f));
}
