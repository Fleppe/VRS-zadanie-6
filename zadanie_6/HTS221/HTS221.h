/*
 * HTS221.h
 *
 *  Created on: Nov 8, 2026
 *      Author: filip
 */

#ifndef HTS221_H_
#define HTS221_H_
#include <stdint.h>

#define HTS221_I2C_ADDRESS          0xBEU

#define HTS221_WHO_AM_I_ADDRESS     0x0FU
#define HTS221_WHO_AM_I_VALUE       0xBCU

#define HTS221_AV_CONF              0x10U
#define HTS221_CTRL_REG1            0x20U
#define HTS221_STATUS_REG           0x27U

#define HTS221_HUMIDITY_OUT_L       0x28U
#define HTS221_TEMP_OUT_L           0x2AU

#define HTS221_H0_RH_X2             0x30U
#define HTS221_H1_RH_X2             0x31U
#define HTS221_T0_DEGC_X8           0x32U
#define HTS221_T1_DEGC_X8           0x33U
#define HTS221_T1_T0_MSB            0x35U
#define HTS221_H0_T0_OUT_L          0x36U
#define HTS221_H1_T0_OUT_L          0x3AU
#define HTS221_T0_OUT_L             0x3CU
#define HTS221_T1_OUT_L             0x3EU

#define HTS221_AUTO_INCREMENT       0x80U

#define HTS221_CTRL1_PD             0x80U
#define HTS221_CTRL1_BDU            0x04U
#define HTS221_CTRL1_ODR_ONE_SHOT   0x00U
#define HTS221_CTRL1_ODR_1HZ        0x01U
#define HTS221_CTRL1_ODR_7HZ        0x02U
#define HTS221_CTRL1_ODR_12_5HZ     0x03U

#define HTS221_STATUS_T_DA          0x01U
#define HTS221_STATUS_H_DA          0x02U


void hts221_register_callbacks(void *read_fn, void *write_fn);

#endif
