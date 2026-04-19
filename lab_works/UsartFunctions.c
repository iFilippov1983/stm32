#include "UsartFunctions.h"

const char *external_string = "hello!";
char hello_str[] = "Hello from F103!\r\n";

uint8_t rx_byte;
uint8_t rx_buffer[RX_BUFFER_SIZE];

volatile UART_STATE uart_state = WAITING;
volatile uint8_t rx_index = 0;

void SetUsartState(UART_STATE state)
{
	uart_state = state;
}

void SendStr_Blocking(UART_HandleTypeDef *huart, uint32_t delay_ms, uint32_t timeout_ms)
{
	HAL_UART_Transmit(huart, hello_str, strlen(hello_str), timeout_ms);
	HAL_Delay(delay_ms);
}

void SendStr_IT(UART_HandleTypeDef *huart)
{
	if(uart_state == READY)
	{
		HAL_UART_Transmit_IT(huart, hello_str, strlen(hello_str));
		uart_state = SENDING;
	}
}

void SendStr_IT_TIM(UART_HandleTypeDef *huart, TIM_HandleTypeDef *htim)
{
	if(uart_state == READY)
	{
		HAL_UART_Transmit_IT(huart, hello_str, strlen(hello_str));
		HAL_TIM_Base_Stop_IT(htim);
		uart_state = SENDING;
	}
	else if(uart_state == DONE)
	{
		HAL_TIM_Base_Start_IT(htim);
		uart_state = WAITING;
	}
}

void SendStr_AfterReceive(UART_HandleTypeDef *huart)
{
	if(uart_state == READY)
	{
		if(strstr((char*)rx_buffer, external_string) != NULL)
		{
			HAL_UART_Transmit_IT(huart, hello_str, strlen(hello_str));
			uart_state = SENDING;
		}
		else
		{
			uart_state = READING;
		}
	}
	else if(uart_state == DONE)
	{
		uart_state = WAITING;
	}
}

void ReseiveStr_ByByte(UART_HandleTypeDef *huart)
{
	HAL_UART_Receive_IT(huart, &rx_byte, 1);
}

void IterateRxByteInBuffer(UART_HandleTypeDef *huart)
{
	if(rx_index < RX_BUFFER_SIZE - 1)
	{
		rx_buffer[rx_index] = rx_byte;
		rx_index++;
	}

	if(rx_byte == '\r')
	{
		rx_buffer[rx_index] = '\0';
		rx_index = 0;
		uart_state = READY;
	}

	ReseiveStr_ByByte(huart);
}


