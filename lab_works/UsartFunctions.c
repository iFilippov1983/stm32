#include "UsartFunctions.h"

char hello_str[] = "Hello from F103! Button pressed!\r\n";

volatile UART_STATE uart_state = WAITING;

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

