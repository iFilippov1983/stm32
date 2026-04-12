#define I2C_BUFFER_SIZE 16
#define SLAVE_I2C_ADDR (0x30 << 1) // (0x30 - 7-битный адрес) << 1 = 0x60 сдвигаем на 1 разряд влево в двоичном представлении из-за особенности работы i2c

#ifdef HAL_I2C_MODULE_ENABLED

#include "main.h"
#include "stm32f1xx_hal.h"

#ifndef I2CFUNCTIONS_H_
#define I2CFUNCTIONS_H_

void HandleMainThread
(
	I2C_HandleTypeDef* hi2c,
	GPIO_TypeDef* LED_GPIO_Port,
	uint16_t LED_Pin,
	const char* MASTER_STR,
	const char* SLAVE_STR,
	uint8_t use_dma
);
void SetTransferCompleteStatus(uint8_t status);
void SetReceiveCompleteStatus(uint8_t status);
void SetI2cErrorStatus(uint8_t status);


#endif /* I2CFUNCTIONS_H_ */

#endif
