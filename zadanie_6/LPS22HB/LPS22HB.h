/*
 * LPS22HB.h
 *
 *  Created on: Nov 8, 2026
 *      Author: filip
 */

#ifndef LPS22HB_H_
#define LPS22HB_H_
#include <stdint.h>

#define LPS22HB_I2C_ADDRESS         0xBAU

#define LPS22HB_WHO_AM_I_ADDRESS    0x0FU
#define LPS22HB_WHO_AM_I_VALUE      0xB1U

#define LPS22HB_CTRL_REG1           0x10U

#define LPS22HB_CTRL1_ODR_10HZ      0x20U

void lps22hb_register_callbacks(void *read_fn, void *write_fn);
uint8_t lps22hb_read(uint8_t reg, uint8_t *data, uint8_t len);
uint8_t lps22hb_write(uint8_t reg, uint8_t *data, uint8_t len);
uint8_t lps22hb_init(void);

#endif /* LPS22HB_H_ */
