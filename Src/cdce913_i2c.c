/**
  ******************************************************************************
  * @file           : cdce913_i2c.h
  * @brief          : Header for cdce913_i2c file.
  *                   This file contains the functions for managing the CDCE913
  *                   clock generator via I2C bus with an STM32 I2C HAL API
  *                   as a part of the lboard2 firmware.
  *                   lboard2 schematics and pcb files are available at:
  *                   https://github.com/electrodyssey/lboard2
  *
  *                  
  ******************************************************************************
  */


#include "cdce913_i2c.h"
#include "main.h"

//static uint16_t CDCE913_CONFIG_LEN = 31;

/*
 * modify for your application
 * TI provides a GUI application  ClockPro(TM) for an easy setup
 * ClockPro(TM) allows the export of registers in a hex dump
 * config is valid for: 
 * Y1=110.592MHz; Y2=12.288MHz; Y3=3.072MHz NO spread spectrum
 */
/*
static uint8_t CDCE913_CONFIG_INIT [] =
  {
    0x01, //byte0 - read only although ACK'ed by I2C write
    0x00,
    0xB4,//byte02
    0x02,
    0x02,//04
    0x80,
    0x40,//06
    0x00,//07
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,//19
    0x6D,//20
    0x02,
    0x12,//22
    0x48,
    0xC0,//24
    0x04,
    0x82,//26
    0x07,
    0xC0,//28
    0x04,
    0x82,//30
    0x04
  };
*/



//Y1:75.264 Y2:11.2896 - no spread spectrum
/*
static uint8_t CDCE913_CONFIG_INIT [] =
{
    0x81, //00
    0x01,
    0xB4,
    0x03,
    0x02,
    0x80,
    0x40,
    0x00,
    0x00,
    0x00,
    0x00, //10
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x6D,//20
    0x02,
    0x14,
    0x14,
    0xC4,
    0x08,
    0x82,
    0x07,
    0x00,
    0x40,
    0x02,
    0x08 //30
};
*/


//5.5 mhz test
/*
static uint8_t CDCE913_CONFIG_INIT [] =
{
    0x81, //0
    0x01,
    0xB4,
    0x28,
    0x02,
    0x80,
    0x40,
    0x00,
    0x00,
    0x00,//9 
    0x00,//10
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x6D,
    0x02,//21
    0x12,
    0x48,
    0xC0,
    0x04,
    0x82,
    0x07,
    0x00,
    0x40,
    0x02,//30
    0x08
};
*/


//Y1:56.448 Y2:11.2896 - no spread spectrum
static uint8_t CDCE913_CONFIG_INIT [] =
{
	0x81,
	0x01,
	0xB4,
	0x04,
	0x02,
	0x80,
	0x40,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x6D,
	0x02,
	0x14,
	0x14,
	0xC4,
	0x08,
	0x82,
	0x07,
	0x00,
	0x40,
	0x02,
	0x08
};


//Y1:112.896 Y2:11.2896
/*
static uint8_t CDCE913_CONFIG_INIT [] =
{
	0x81,
	0x01,
	0xB4,
	0x01,
	0x02,
	0x80,
	0x40,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x6D,
	0x02,
	0x0A,
	0x0A,
	0x62,
	0x08,
	0x82,
	0x08,
	0x00,
	0x40,
	0x02,
	0x08
};
*/


HAL_StatusTypeDef cdce913_i2c_read_config_byte (I2C_HandleTypeDef *hi2c, uint8_t dev_addr, uint8_t mem_addr, uint8_t *cb)
{
  HAL_StatusTypeDef res = 0;

#ifdef DBG_PRINT
  printf ("reading addr 0x[%.2x] from device 0x[%.2x]\n", mem_addr, dev_addr);
#endif
  res =  HAL_I2C_Mem_Read(hi2c, dev_addr , mem_addr | (uint8_t)0x80, I2C_MEMADD_SIZE_8BIT, cb, 1, 100);
#ifdef DBG_PRINT
  printf ("status 0x[%.2x] reading addr 0x[%.2x] from device 0x[%.2x] = 0x[%.2x]\n", res, mem_addr, dev_addr, *cb);
#endif

  
  return res;
}


/*
TODO account for a transfer size - first byte is a transmitted data size?
*/
HAL_StatusTypeDef cdce913_i2c_read_config_block (I2C_HandleTypeDef *hi2c, uint8_t dev_addr, uint8_t mem_addr, uint8_t *cb, uint16_t size)
{
  HAL_StatusTypeDef res = 0;

#ifdef DBG_PRINT
  printf ("reading %d bytes starting from 0x[%.2x] from device 0x[%.2x]\n", size, mem_addr, dev_addr);
#endif
 res =  HAL_I2C_Mem_Read(hi2c, dev_addr, mem_addr, size, cb, size, 1000);
#ifdef DBG_PRINT
 printf ("block readback is done with status 0x[%.2x]\n", res);
 uint8_t i;

 for (i = 0; i < size; i++)
     printf ("0x%.2x = 0x[%.2x]\n", i, cb[i]);
#endif

  
  return res;
}
 

HAL_StatusTypeDef cdce913_i2c_write_config_byte (I2C_HandleTypeDef *hi2c, uint8_t dev_addr, uint8_t mem_addr, uint8_t *cb)
{
  HAL_StatusTypeDef res = 0;

#ifdef DBG_PRINT
  printf ("writing addr 0x[%.2x] = [%.2x] on device 0x[%.2x]\n", mem_addr, *cb, dev_addr);
#endif
  res =  HAL_I2C_Mem_Write(hi2c, dev_addr, mem_addr | (uint8_t)0x80, 1, cb, 1, 100);
#ifdef DBG_PRINT
 printf ("status 0x[%.2x] writing addr 0x[%.2x] with -> 0x[%.2x] to device 0x[%.2x]\n", res, mem_addr, *cb, dev_addr);
#endif
  
 return res;
}


/*
  TODO account for a transfer size
*/
HAL_StatusTypeDef cdce913_i2c_write_config_block (I2C_HandleTypeDef *hi2c, uint8_t dev_addr, uint8_t mem_addr, uint8_t *cb, uint8_t size)
{
  HAL_StatusTypeDef res = 0;
  
#ifdef DBG_PRINT
  printf ("writing block of %d bytes to device 0x[%.2x]\n", size, dev_addr);
#endif

  res =  HAL_I2C_Mem_Write(hi2c, dev_addr, mem_addr, size, cb, size, 100);
  
#ifdef DBG_PRINT
  printf ("done writing block of size %d to device 0x[%.2x] with status 0x[%.2x]\n", size, dev_addr, res);
#endif

  return res;
}


void cdce913_i2c_push_config (I2C_HandleTypeDef *hi2c)
{
  uint8_t mem_addr;
  
  for (mem_addr = 2; mem_addr < 5; mem_addr++)
    cdce913_i2c_write_config_byte (hi2c, CDCE913_I2C_ADDR, mem_addr, &CDCE913_CONFIG_INIT[mem_addr]);
  
  for (mem_addr = 20; mem_addr < 32; mem_addr++)
    cdce913_i2c_write_config_byte (hi2c, CDCE913_I2C_ADDR, mem_addr, &CDCE913_CONFIG_INIT[mem_addr]);
}


void cdce913_output_switch (uint8_t en)
{
#ifdef DBG_PRINT
 printf ("cdce913 output switch [%d] \n", en);
#endif

 if (0 == en)
   HAL_GPIO_WritePin(GPIOB, I2C_CLK_ENA_Pin, GPIO_PIN_RESET);
 else
   HAL_GPIO_WritePin(GPIOB, I2C_CLK_ENA_Pin, GPIO_PIN_SET);
}

/************************ (C) COPYRIGHT electrodyssey *****END OF FILE****/
