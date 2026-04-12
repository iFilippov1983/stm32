#define SPI_BUFFER_SIZE 16

#ifdef HAL_SPI_MODULE_ENABLED

#include "main.h"
#include "stm32f1xx_hal.h"

#ifndef SPIFUNCTIONS_H_
#define SPIFUNCTIONS_H_


void HandleMainThread
(
	SPI_HandleTypeDef *hspi,
	GPIO_TypeDef *LED_GPIOx,
	uint16_t LED_GPIO_Pin,
	const char* MASTER_STR,
	const char* MASTER_POLL_STR,
	const char* SLAVE_STR
);
void HandleGpioCallback(SPI_HandleTypeDef *hspi);
void SetTransferCompleteStatus(uint8_t status);

#endif /* SPIFUNCTIONS_H_ */

#endif
