/**
  ******************************************************************************
  * @file           : cdce913_i2c.h
  * @brief          : Header for cdce913_i2c file.
  *                   This file contains the defines for managing the CDCE913
  *                   clock generator via I2C bus with an STM32 I2C HAL API
  *                  
  ******************************************************************************
  */

#ifndef __CDCE913_I2C_H__
#define __CDCE913_I2C_H__


#ifdef __cplusplus
 extern "C" {
#endif


#include "stm32f4xx_hal.h"

static uint16_t CDCE913_I2C_ADDR = 0xCA;


HAL_StatusTypeDef cdce913_i2c_read_config_byte  (
						 I2C_HandleTypeDef *hi2c,
						 uint8_t dev_addr,
						 uint8_t mem_addr,
						 uint8_t *cb);

HAL_StatusTypeDef cdce913_i2c_write_config_byte (
						 I2C_HandleTypeDef *hi2c,
						 uint8_t dev_addr,
						 uint8_t mem_addr,
						 uint8_t *cb);
/*
HAL_StatusTypeDef cdce913_i2c_write_config_block (
						  I2C_HandleTypeDef *hi2c,
						  uint8_t dev_addr,
						  uint8_t mem_addr,
						  uint8_t *cb,
						  uint8_t size);
*/

/*
HAL_StatusTypeDef cdce913_i2c_read_config_block (I2C_HandleTypeDef *hi2c,
						 uint8_t dev_addr,
						 uint8_t mem_addr,
						 uint8_t *cb,
						 uint16_t size);
*/

void cdce913_i2c_push_config (I2C_HandleTypeDef *hi2c);
  

void cdce913_output_switch (uint8_t en);


#ifdef __cplusplus
}
#endif
   

#endif
/************************ (C) COPYRIGHT electrodyssey *****END OF FILE****/
