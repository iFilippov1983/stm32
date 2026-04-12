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

#define PWM_BUFFER_SIZE 5000

#ifndef LABWORKS_H_
#define LABWORKS_H_

void BlinkLed(int blinkPeriod, int bliksAmount);
void BlinkLed_EXTI_WithDelay(int blinkPeriod);
void BlinkLed_EXTI_WithTick();
void LightLedIfButtonPressed(void);
void LightLedIfButtonPressed_EXTI();

void HandleExtiCallback_Simple(uint16_t GPIO_Pin);
void HandleExtiCallback_SwitchFr(uint16_t GPIO_Pin);

GPIO_PinState IsButtonPressed();
void ReconfigTim(TIM_HandleTypeDef *htim, uint32_t channel, uint16_t ccrValue);
void ReconfigTim_IfButtonPressed(TIM_HandleTypeDef *htim, uint32_t channel, uint16_t ccrValuePr, uint16_t ccrValueRe);

void LedToggle();
void DelayMs(uint16_t ms, TIM_HandleTypeDef *htim);
int DelayWithCounter_Check(int ms, TIM_HandleTypeDef *htim);
void DelayWithCounter_Reset();
void BlinkLed_TIM_DelayWithCounter(int ms, TIM_HandleTypeDef *htim);
void BlinkLed_TIM_DelayWithCounter(int ms, TIM_HandleTypeDef *htim);

void FillPwm(uint16_t *ppwm_buffer, uint16_t size);

#endif /* LABWORKS_H_ */
