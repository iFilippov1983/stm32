#include "main.h"
#include "stm32f1xx_hal.h"

typedef enum
{
	FR_0 = 0u, FR_200 = 200u, FR_1000 = 1000u, FR_2000 = 2000u
} LED_FR;

#ifndef LABWORKS_H_
#define LABWORKS_H_

void BlinkLed(int blinkPeriod, int bliksAmount);
void BlinkLed_EXTI_WithDelay(int blinkPeriod);
void BlinkLed_EXTI_WithTick();
void LightLedIfButtonPressed(void);
void LightLedIfButtonPressed_EXTI();

void HandleExtiCallback_Simple(uint16_t GPIO_Pin);
void HandleExtiCallback_SwitchFr(uint16_t GPIO_Pin);

void LedToggle();
void DelayMs(uint16_t ms, TIM_HandleTypeDef *htim2);
int DelayWithCounter_Check(int ms, TIM_HandleTypeDef *htim2);
void DelayWithCounter_Reset();

#endif /* LABWORKS_H_ */
