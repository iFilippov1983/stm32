#include "main.h"
#include "stm32f1xx_hal.h"

typedef enum
{
	WAITING, READY, SENDING, DONE
}UART_STATE;

#ifndef USARTFUNCTIONS_H_
#define USARTFUNCTIONS_H_

void SetUsartState(UART_STATE state);
void SendStr_Blocking(UART_HandleTypeDef *huart, uint32_t delay_ms, uint32_t timeout_ms);
void SendStr_IT(UART_HandleTypeDef *huart);
void SendStr_IT_TIM(UART_HandleTypeDef *huart, TIM_HandleTypeDef *htim);

#endif /* USARTFUNCTIONS_H_ */
