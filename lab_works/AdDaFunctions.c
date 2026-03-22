#include "AdDaFunctions.h"

float volt_buffer[BUFFER_SIZE];
uint32_t adc_buffer[BUFFER_SIZE];
uint8_t buffer_index = 0;

void RawToVolt(uint32_t *pbuf_raw, float* pbuf_float, uint8_t size)
{
	for(int i = 0; i < size; i++)
	{
		pbuf_float[i] = pbuf_raw[i] * ADC_REF / ADC_RES;
	}
}

void AdcExecution_SingleConversion(ADC_HandleTypeDef* hadc)
{
	HAL_ADC_Start(hadc);
	if(HAL_ADC_PollForConversion(hadc, TIMEOUT_100) == HAL_OK)
	{
		uint32_t adc_value = HAL_ADC_GetValue(hadc);
		if(buffer_index < BUFFER_SIZE)
		{
			adc_buffer[buffer_index] = adc_value;
			buffer_index++;
		}
		else
		{
			RawToVolt(adc_buffer, volt_buffer, BUFFER_SIZE);
			buffer_index = 0;
		}
	}
	HAL_ADC_Stop(hadc);
}
