/*
 * LPS25HB.h
 *
 *  Created on: Nov 8, 2026
 *      Author: filip
 */

#ifndef LPS25HB_H_
#define LPS25HB_H_
#include <stdint.h>
#include <math.h>

#define LPS25HB_I2C_ADDRESS         0xBAU

#define LPS25HB_WHO_AM_I_ADDRESS    0x0FU
#define LPS25HB_WHO_AM_I_VALUE      0xBDU

#define LPS25HB_CTRL_REG1           0x20U

#define LPS25HB_AUTO_INCREMENT      0x80U

#define LPS25HB_CTRL1_PD            0x80U
#define LPS25HB_CTRL1_BDU           0x04U
#define LPS25HB_CTRL1_ODR_12_5HZ    0x30U

#define LPS25HB_PRESS_OUT_XL        0x28U
#define LPS25HB_PRESSURE_SENSITIVITY 4096.0f

void lps25hb_register_callbacks(void *read_fn, void *write_fn);
uint8_t lps25hb_read(uint8_t reg, uint8_t *data, uint8_t len);
uint8_t lps25hb_write(uint8_t reg, uint8_t *data, uint8_t len);
uint8_t lps25hb_init(void);
uint8_t get_pressure(float *pressure);
float calculate_altitude(float pressure, float reference_pressure);
#endif /* LPS25HB_H_ */
