#include "main.h"
#include "stm32f1xx_hal.h"

#ifndef SPIFUNCTIONS_H_
#define SPIFUNCTIONS_H_

#define SPI_BUFFER_SIZE 16

typedef enum
{
	STATE_SEND_MSG,
	STATE_WAIT_FOR_MASTER_MSG_ACK,
	STATE_SEND_POLL,
	STATE_WAIT_FOR_SLAVE_MSG_ACK
} MasterState_t;

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
