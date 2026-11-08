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
#define LPS22HB_CTRL_REG2           0x11U
#define LPS22HB_STATUS              0x27U
#define LPS22HB_PRESS_OUT_XL        0x28U
#define LPS22HB_TEMP_OUT_L          0x2BU

#define LPS22HB_CTRL1_ODR_POWER_DOWN 0x00U
#define LPS22HB_CTRL1_ODR_1HZ       0x10U
#define LPS22HB_CTRL1_ODR_10HZ      0x20U
#define LPS22HB_CTRL1_ODR_25HZ      0x30U
#define LPS22HB_CTRL1_ODR_50HZ      0x40U
#define LPS22HB_CTRL1_ODR_75HZ      0x50U
#define LPS22HB_CTRL1_EN_LPFP       0x08U
#define LPS22HB_CTRL1_LPFP_CFG      0x04U


#define LPS22HB_CTRL2_IF_ADD_INC    0x10U


#define LPS22HB_STATUS_P_DA         0x01U
#define LPS22HB_STATUS_T_DA         0x02U


#define LPS22HB_PRESSURE_SENSITIVITY 4096.0f

void lps22hb_register_callbacks(void *read_fn, void *write_fn);

#endif /* LPS22HB_H_ */
