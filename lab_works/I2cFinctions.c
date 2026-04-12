//#ifdef HAL_I2C_MODULE_ENABLED

#include <string.h>
#include "I2cFunctions.h"
#include "LabWorks.h"

MasterState_t master_state = STATE_SEND_MSG;

volatile uint8_t i2c_error = 0;
volatile uint8_t receive_complete = 0;
volatile uint8_t transfer_complete = 0;

uint8_t master_tx_buf[I2C_BUFFER_SIZE];
uint8_t master_rx_buf[I2C_BUFFER_SIZE];

void SetTransferCompleteStatus(uint8_t status)
{
	transfer_complete = status;
}

void SetReceiveCompleteStatus(uint8_t status)
{
	receive_complete = status;
}

void SetI2cErrorStatus(uint8_t status)
{
	i2c_error = status;
}

void HandleMainThread
(
	I2C_HandleTypeDef* hi2c,
	GPIO_TypeDef* LED_GPIO_Port,
	uint16_t LED_Pin,
	const char* MASTER_STR,
	const char* SLAVE_STR,
	uint8_t use_dma
)
{
	if (i2c_error)
	{
		SetI2cErrorStatus(0);
		HAL_Delay(500);
		master_state = STATE_SEND_MSG;
	}

	if (HAL_I2C_GetState(hi2c) != HAL_I2C_STATE_READY)
	{
		return;
	}

	switch (master_state)
	{
	case STATE_SEND_MSG:
		SetTransferCompleteStatus(0);
		strcpy((char*)master_tx_buf, MASTER_STR);

		if(use_dma)
		{
			if (HAL_I2C_Master_Transmit_DMA(hi2c, SLAVE_I2C_ADDR, master_tx_buf, I2C_BUFFER_SIZE) != HAL_OK)
			{
				Error_Handler();
			}
		}
		else
		{
			if (HAL_I2C_Master_Transmit_IT(hi2c, SLAVE_I2C_ADDR, master_tx_buf, I2C_BUFFER_SIZE) != HAL_OK)
			{
				Error_Handler();
			}
		}

		master_state = STATE_WAIT_FOR_MASTER_MSG_ACK;
		break;

	case STATE_WAIT_FOR_MASTER_MSG_ACK:
		if (transfer_complete)
		{
			SetTransferCompleteStatus(0);
			HAL_Delay(10);
			master_state = STATE_RECEIVE_MSG;
		}
		break;

	case STATE_RECEIVE_MSG:
		if(use_dma)
		{
			if (HAL_I2C_Master_Receive_DMA(hi2c, SLAVE_I2C_ADDR, master_rx_buf, I2C_BUFFER_SIZE) != HAL_OK)
			{
				Error_Handler();
			}
		}
		else
		{
			if (HAL_I2C_Master_Receive_IT(hi2c, SLAVE_I2C_ADDR, master_rx_buf, I2C_BUFFER_SIZE) != HAL_OK)
			{
				Error_Handler();
			}
		}

		master_state = STAE_WAIT_FOR_RECEIVE;
		break;

	case STAE_WAIT_FOR_RECEIVE:
		if (receive_complete)
		{
			SetReceiveCompleteStatus(0);

			if (strcmp((char*)master_rx_buf, SLAVE_STR) == 0)
			{
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
		}

		HAL_Delay(1000);
		master_state = STATE_SEND_MSG;
		break;

	case STATE_SEND_POLL:
	case STATE_WAIT_FOR_SLAVE_MSG_ACK:
		break;
	}
}

//#endif


