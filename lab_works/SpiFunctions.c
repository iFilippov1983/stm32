#ifdef HAL_SPI_MODULE_ENABLED

#include <string.h>
#include "SpiFunctions.h"

uint8_t master_tx_buf[SPI_BUFFER_SIZE];
uint8_t master_rx_buf[SPI_BUFFER_SIZE];

MasterState_t master_state = STATE_SEND_MSG;

volatile uint8_t transfer_complete = 0;

void HandleMainThread
(
	SPI_HandleTypeDef *hspi,
	GPIO_TypeDef *LED_GPIOx,
	uint16_t LED_GPIO_Pin,
	const char* MASTER_STR,
	const char* MASTER_POLL_STR,
	const char* SLAVE_STR
)
{
	if(HAL_SPI_GetState(hspi) != HAL_SPI_STATE_READY)
	{
		return;
	}

	switch(master_state)
{
		case STATE_SEND_MSG:
			/* подготовка строки и отправка TramsmitReceive_IT */
			strcpy((char*)master_tx_buf, MASTER_STR);

			HAL_GPIO_WritePin(SPI1_NSS_GPIO_Port, SPI1_NSS_Pin, GPIO_PIN_RESET);

			if(HAL_SPI_TransmitReceive_IT(hspi, master_tx_buf, master_rx_buf, SPI_BUFFER_SIZE) != HAL_OK)
			{
				Error_Handler();
			}

			master_state = STATE_WAIT_FOR_MASTER_MSG_ACK;
			break;

		case STATE_WAIT_FOR_MASTER_MSG_ACK:
			if(transfer_complete)
			{
				HAL_Delay(1);
				master_state = STATE_SEND_POLL;
			}
			break;

		case STATE_SEND_POLL:
			transfer_complete = 0;

			/* подготовка мусорной строки и отправка TramsmitReceive_IT */
			strcpy((char*)master_tx_buf, MASTER_POLL_STR);

			HAL_GPIO_WritePin(SPI1_NSS_GPIO_Port, SPI1_NSS_Pin, GPIO_PIN_RESET);

			if(HAL_SPI_TransmitReceive_IT(hspi, master_tx_buf, master_rx_buf, SPI_BUFFER_SIZE) != HAL_OK)
			{
				Error_Handler();
			}

			master_state = STATE_WAIT_FOR_SLAVE_MSG_ACK;
			break;

		case STATE_WAIT_FOR_SLAVE_MSG_ACK:
			if(transfer_complete)
			{
				if(strcmp((char*)master_rx_buf, SLAVE_STR) == 0)
				{
					/* если "Slave Message", то ОК*/
					HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
					HAL_Delay(500);
					HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
				}
			else
				{
					HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
					HAL_Delay(250);
					HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
					HAL_Delay(250);
					HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
					HAL_Delay(250);
					HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
				}

				HAL_Delay(1000);
				master_state = STATE_SEND_MSG;
			}
			break;
	}
}

void HandleGpioCallback(SPI_HandleTypeDef *hspi)
{
	if(HAL_SPI_GetState(hspi) == HAL_SPI_STATE_READY)
	{
		if(HAL_SPI_TransmitReceive_IT(hspi, master_tx_buf, master_rx_buf, SPI_BUFFER_SIZE) != HAL_OK)
		{
			Error_Handler();
		}
	}
}

void SetTransferCompleteStatus(uint8_t status)
{
	transfer_complete = status;
}

#endif
