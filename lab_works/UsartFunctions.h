#include "main.h"
#include "stm32f1xx_hal.h"

typedef enum
{
	WAITING, READY, SENDING, READING, DONE
}UART_STATE;

#define RX_BUFFER_SIZE 64

#ifndef USARTFUNCTIONS_H_
#define USARTFUNCTIONS_H_

void SetUsartState(UART_STATE state);
void SendStr_Blocking(UART_HandleTypeDef *huart, uint32_t delay_ms, uint32_t timeout_ms);
void SendStr_IT(UART_HandleTypeDef *huart);
void SendStr_IT_TIM(UART_HandleTypeDef *huart, TIM_HandleTypeDef *htim);
void SendStr_AfterReceive(UART_HandleTypeDef *huart);
void ReseiveStr_ByByte(UART_HandleTypeDef *huart);
void IterateRxByteInBuffer(UART_HandleTypeDef *huart);

#endif /* USARTFUNCTIONS_H_ */
