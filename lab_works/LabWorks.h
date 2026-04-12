#include "main.h"
#include "stm32f1xx_hal.h"

typedef enum
{
	FR_0 = 0u, FR_200 = 200u, FR_1000 = 1000u, FR_2000 = 2000u
} LED_FR;

typedef enum
{
	RELEASED, PRESSED
} BUTTON_STATE;

typedef enum
{
	STATE_SEND_MSG,
	STATE_WAIT_FOR_MASTER_MSG_ACK,
	STATE_SEND_POLL,
	STATE_WAIT_FOR_SLAVE_MSG_ACK,
	STATE_RECEIVE_MSG,
	STAE_WAIT_FOR_RECEIVE
} MasterState_t;

#ifndef LABWORKS_H_
#define LABWORKS_H_

const char* MASTER_STR = "Master Message";
const char* SLAVE_STR = "Slave Message";
const char* SLAVE_ERROR_STR = "Slave Error";
const char* MASTER_POLL_STR = "Get Response...";

void BlinkLed(int blinkPeriod, int bliksAmount);
void BlinkLed_EXTI_WithDelay(int blinkPeriod);
void BlinkLed_EXTI_WithTick();
void LightLedIfButtonPressed(void);
void LightLedIfButtonPressed_EXTI();

void HandleExtiCallback_Simple(uint16_t GPIO_Pin);
void HandleExtiCallback_SwitchFr(uint16_t GPIO_Pin);

#ifdef HAL_TIM_MODULE_ENABLED

GPIO_PinState IsButtonPressed();
void ReconfigTim(TIM_HandleTypeDef *htim, uint32_t channel, uint16_t ccrValue);
void ReconfigTim_IfButtonPressed(TIM_HandleTypeDef *htim, uint32_t channel, uint16_t ccrValuePr, uint16_t ccrValueRe);

void LedToggle();
void DelayMs(uint16_t ms, TIM_HandleTypeDef *htim);
int DelayWithCounter_Check(int ms, TIM_HandleTypeDef *htim);
void DelayWithCounter_Reset();
void BlinkLed_TIM_DelayWithCounter(int ms, TIM_HandleTypeDef *htim);
void BlinkLed_TIM_DelayWithCounter(int ms, TIM_HandleTypeDef *htim);

#endif

#endif /* LABWORKS_H_ */
