#ifdef HAL_TIM_MODULE_ENABLED

#include "LabWorks.h"

LED_FR ledFreq = FR_0;
uint32_t blinkStartTime = 0;
uint32_t blinkHalfPeriod = 0;
int ledOn = 0;
int pushesCounter = 0;
int ledMsCounter = 0;
BUTTON_STATE buttonState = RELEASED;

/*lab_1, lab_2 -------------------------------------------------*/

void BlinkLed(int blinkPeriod, int bliksAmount)
{
	for (int i = 0; i < bliksAmount; i++)
	{
		HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
		HAL_Delay(blinkPeriod);
		HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
		HAL_Delay(blinkPeriod);
	}
}

void BlinkLed_EXTI_WithDelay(int blinkPeriod)
{
	if (!(HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_SET))
	{
		if (ledOn == GPIO_PIN_RESET)
		{
			ledOn = GPIO_PIN_SET;
			HAL_GPIO_WritePin(B1_STATE_GPIO_Port, B1_STATE_Pin, GPIO_PIN_SET);
			HAL_Delay(blinkPeriod);
			HAL_GPIO_WritePin(B1_STATE_GPIO_Port, B1_STATE_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
			HAL_Delay(blinkPeriod);
			ledOn = GPIO_PIN_RESET;
		}
	}
	else
	{
		ledOn = GPIO_PIN_RESET;
		HAL_GPIO_WritePin(B1_STATE_GPIO_Port, B1_STATE_Pin, ledOn);
		HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, ledOn);
	}
}

void BlinkLed_EXTI_WithTick()
{
	if (!(HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_SET))
	{
		HAL_GPIO_WritePin(B1_STATE_GPIO_Port, B1_STATE_Pin, GPIO_PIN_SET);

		if (ledFreq != FR_0)
		{
			uint32_t currentTick = HAL_GetTick();
			if (currentTick - blinkStartTime >= blinkHalfPeriod)
			{
				blinkStartTime = currentTick;
				ledOn = !ledOn;
				HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, ledOn ? GPIO_PIN_SET : GPIO_PIN_RESET);
			}
		}
	}
	else
	{
		HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(B1_STATE_GPIO_Port, B1_STATE_Pin, GPIO_PIN_RESET);
	}
}

void LightLedIfButtonPressed(void)
{
	uint8_t button_state = !HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin);

	HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, button_state);
}

void LightLedIfButtonPressed_EXTI()
{
	if (!(HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_SET))
	{
		HAL_GPIO_WritePin(B1_STATE_GPIO_Port, B1_STATE_Pin, GPIO_PIN_SET);
	}
	else
	{
		HAL_GPIO_WritePin(B1_STATE_GPIO_Port, B1_STATE_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
	}
}

/*lab_4 -------------------------------------------------*/

void HandleExtiCallback_Simple(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == GPIO_PIN_9)
	{
		HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
	}
}

void HandleExtiCallback_SwitchFr(uint16_t GPIO_Pin)
{
	if (GPIO_Pin == GPIO_PIN_9)
	{
		pushesCounter++;
	    switch (pushesCounter % 4)
	    {
	      case 1:
	    	  ledFreq = FR_200;
	    	  blinkHalfPeriod = 100;
	    	  break;  // 200мс

	      case 2:
	    	  ledFreq = FR_1000;
	    	  blinkHalfPeriod = 500;
	    	  break; // 1000мс

	      case 3:
	    	  ledFreq = FR_2000;
	    	  blinkHalfPeriod = 1000;
	    	  break; // 2000мс

	      default:
	    	  ledFreq = FR_0;
	    	  HAL_GPIO_WritePin(B1_STATE_GPIO_Port, B1_STATE_Pin, GPIO_PIN_RESET);
	    	  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
	    	  break;
	    }

	    if (ledFreq != FR_0) {
	      blinkStartTime = HAL_GetTick();
	      ledOn = 0;
	    }
	}
}

/*lab_4 -------------------------------------------------*/

GPIO_PinState IsButtonPressed()
{
	return !HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin);
}

void ReconfigTim(TIM_HandleTypeDef *htim, uint32_t channel, uint16_t ccrValue)
{
	HAL_TIM_PWM_Stop_IT(htim, channel);

	TIM_OC_InitTypeDef sConfigOC = {0};
	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = ccrValue;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

	HAL_TIM_PWM_ConfigChannel(htim, &sConfigOC, channel);

	HAL_TIM_PWM_Start_IT(htim, channel);
}

void ReconfigTim_IfButtonPressed(TIM_HandleTypeDef *htim, uint32_t channel, uint16_t ccrValuePr, uint16_t ccrValueRe)
{
	switch(buttonState)
		  {
		  case RELEASED:
			  if(IsButtonPressed())
			  {
				  ReconfigTim(htim, channel, ccrValuePr);
				  buttonState = PRESSED;
			  }
			  break;
		  case PRESSED:
			  if(!IsButtonPressed())
			  {
				  ReconfigTim(htim, channel, ccrValueRe);
			  	  buttonState = RELEASED;
			  }
			  break;
		  }
}

void LedToggle()
{
	HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
}

/*Bad delay implementation*/
void DelayMs(uint16_t ms, TIM_HandleTypeDef *htim)
{
	for(uint16_t i = 0; i < ms; i++)
	{
		while(__HAL_TIM_GET_FLAG(htim, TIM_FLAG_UPDATE) == RESET);

		__HAL_TIM_CLEAR_FLAG(htim, TIM_FLAG_UPDATE);
	}
}

int DelayWithCounter_Check(int ms, TIM_HandleTypeDef *htim)
{
	if(__HAL_TIM_GET_FLAG(htim, TIM_FLAG_UPDATE))
	{
		ledMsCounter++;
		__HAL_TIM_CLEAR_FLAG(htim, TIM_FLAG_UPDATE);
	}
	return ledMsCounter == ms;
}

void DelayWithCounter_Reset()
{
	ledMsCounter = 0;
}

//lab_4 - part 1
void BlinkLed_TIM_DelayWithCounter(int ms, TIM_HandleTypeDef *htim)
{
	if(DelayWithCounter_Check(ms, htim))
	{
		LedToggle();
		DelayWithCounter_Reset();
	}
}

#endif
