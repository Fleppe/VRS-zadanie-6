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

static float t0_degc, t1_degc, h0_rh, h1_rh;
static int16_t t0_out, t1_out, h0_t0_out, h1_t0_out;

uint8_t hts221_read(uint8_t reg, uint8_t *data, uint8_t len)
{
	if(hts_read == 0) return 0;

	if(len > 1) reg |= HTS221_AUTO_INCREMENT;
	return hts_read(HTS221_I2C_ADDRESS, reg, data, len);
}

uint8_t hts221_write(uint8_t reg, uint8_t *data, uint8_t len)
{
	if(hts_write == 0) return 0;

	if(len > 1) reg |= HTS221_AUTO_INCREMENT;
	return hts_write(HTS221_I2C_ADDRESS, reg, data, len);
}

static uint8_t hts221_read_calibration(void)
{
	uint8_t h0, h1;
	uint8_t t0, t1, t_msb;
	uint8_t buf[2];

	if(!hts221_read(HTS221_H0_RH_X2, &h0, 1)) return 0;
	if(!hts221_read(HTS221_H1_RH_X2, &h1, 1)) return 0;
	h0_rh = h0 / 2.0f;
	h1_rh = h1 / 2.0f;


	if(!hts221_read(HTS221_T0_DEGC_X8, &t0, 1)) return 0;
	if(!hts221_read(HTS221_T1_DEGC_X8, &t1, 1)) return 0;
	if(!hts221_read(HTS221_T1_T0_MSB, &t_msb, 1)) return 0;
	t0_degc = (((t_msb & 0x03) << 8) | t0) / 8.0f;
	t1_degc = (((t_msb & 0x0C) << 6) | t1) / 8.0f;

	if(!hts221_read(HTS221_H0_T0_OUT_L, buf, 2)) return 0;
	h0_t0_out = (int16_t)((buf[1] << 8) | buf[0]);

	if(!hts221_read(HTS221_H1_T0_OUT_L, buf, 2)) return 0;
	h1_t0_out = (int16_t)((buf[1] << 8) | buf[0]);

	if(!hts221_read(HTS221_T0_OUT_L, buf, 2)) return 0;
	t0_out = (int16_t)((buf[1] << 8) | buf[0]);

	if(!hts221_read(HTS221_T1_OUT_L, buf, 2)) return 0;
	t1_out = (int16_t)((buf[1] << 8) | buf[0]);

	return 1;
}

uint8_t hts221_init(void)
{
	uint8_t id = 0;
	uint8_t config = HTS221_CTRL1_PD | HTS221_CTRL1_BDU | HTS221_CTRL1_ODR_1HZ;

	if(!hts221_read(HTS221_WHO_AM_I_ADDRESS, &id, 1)) return 0;
	if(id != HTS221_WHO_AM_I_VALUE) return 0;

	if(!hts221_write(HTS221_CTRL_REG1, &config, 1)) return 0;

	return hts221_read_calibration();
}

uint8_t get_temperature(float *temperature)
{
	uint8_t buf[2];
	if(!hts221_read(HTS221_TEMP_OUT_L, buf, 2)) return 0;
	int16_t t_out = (int16_t)((buf[1] << 8) | buf[0]);

	*temperature = t0_degc + (t_out - t0_out) * (t1_degc - t0_degc) / (t1_out - t0_out);
	return 1;
}

uint8_t get_humidity(float *humidity)
{
	uint8_t buf[2];
	if(!hts221_read(HTS221_HUMIDITY_OUT_L, buf, 2)) return 0;

	int16_t h_out = (int16_t)(buf[1] << 8 | buf[0]);

	*humidity = h0_rh + (h_out - h0_t0_out) * (h1_rh - h0_rh) / (h1_t0_out - ho_t0_out);
	return 1;
}
float calculate_altitude(float pressure, float reference_pressure)
{
	return return 44330.0f * (1.0f - powf(pressure / reference_pressure, 1.0f / 5.255f));
}




























