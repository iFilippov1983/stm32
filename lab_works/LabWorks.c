#include "LabWorks.h"

LED_FR _ledFreq = FR_0;
uint32_t _blinkStartTime = 0;
uint32_t _blinkHalfPeriod = 0;
int _ledOn = 0;
int _pushesCounter = 0;

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
		if (_ledOn == GPIO_PIN_RESET)
		{
			_ledOn = GPIO_PIN_SET;
			HAL_GPIO_WritePin(B1_STATE_GPIO_Port, B1_STATE_Pin, GPIO_PIN_SET);
			HAL_Delay(blinkPeriod);
			HAL_GPIO_WritePin(B1_STATE_GPIO_Port, B1_STATE_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
			HAL_Delay(blinkPeriod);
			_ledOn = GPIO_PIN_RESET;
		}
	}
	else
	{
		_ledOn = GPIO_PIN_RESET;
		HAL_GPIO_WritePin(B1_STATE_GPIO_Port, B1_STATE_Pin, _ledOn);
		HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, _ledOn);
	}
}

void BlinkLed_EXTI_WithTick()
{
	if (!(HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_SET))
	{
		HAL_GPIO_WritePin(B1_STATE_GPIO_Port, B1_STATE_Pin, GPIO_PIN_SET);

		if (_ledFreq != FR_0)
		{
			uint32_t currentTick = HAL_GetTick();
			if (currentTick - _blinkStartTime >= _blinkHalfPeriod)
			{
				_blinkStartTime = currentTick;
				_ledOn = !_ledOn;
				HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, _ledOn ? GPIO_PIN_SET : GPIO_PIN_RESET);
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
		_pushesCounter++;
	    switch (_pushesCounter % 4)
	    {
	      case 1:
	    	  _ledFreq = FR_200;
	    	  _blinkHalfPeriod = 100;
	    	  break;  // 200мс

	      case 2:
	    	  _ledFreq = FR_1000;
	    	  _blinkHalfPeriod = 500;
	    	  break; // 1000мс

	      case 3:
	    	  _ledFreq = FR_2000;
	    	  _blinkHalfPeriod = 1000;
	    	  break; // 2000мс

	      default:
	    	  _ledFreq = FR_0;
	    	  HAL_GPIO_WritePin(B1_STATE_GPIO_Port, B1_STATE_Pin, GPIO_PIN_RESET);
	    	  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
	    	  break;
	    }

	    if (_ledFreq != FR_0)
	    {
	      _blinkStartTime = HAL_GetTick();
	      _ledOn = 0;
	    }
	}
}

void HandleExtiCallback_CheckPin(uint16_t GPIO_Pin)
{
	switch(GPIO_Pin)
	{
	case GPIO_PIN_9:
		_ledFreq = FR_200;
		_blinkHalfPeriod = 100;
		break;
	case GPIO_PIN_7:
		_ledFreq = FR_1000;
		_blinkHalfPeriod = 500;
		break;
	case GPIO_PIN_6:
		_ledFreq = FR_2000;
		_blinkHalfPeriod = 1000;
		break;
	default:
		_ledFreq = FR_0;
		HAL_GPIO_WritePin(B1_STATE_GPIO_Port, B1_STATE_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
		break;
	}

	if (_ledFreq != FR_0)
	{
		_blinkStartTime = HAL_GetTick();
		_ledOn = 0;
	}
}
