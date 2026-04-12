//#ifdef HAL_ADC_MODULE_ENABLED

#include "AdDaFunctions.h"

//lab 5 --------------------------
float volt_buffer[BUFFER_SIZE];
uint32_t adc_buffer[BUFFER_SIZE];
uint8_t buffer_index = 0;

//lab 7 --------------------------
float adc_volts[ADC_BUF_LEN];
uint16_t adc_buf[ADC_BUF_LEN];
uint16_t adc_buf_actual[ADC_BUF_LEN];

volatile uint8_t data_ready = 0;

//lab 5 functions --------------------------
void Raw32ToVolt(uint32_t *pbuf_raw, float* pbuf_float, uint8_t size)
{
	for(int i = 0; i < size; i++)
	{
		pbuf_float[i] = pbuf_raw[i] * ADC_REF / ADC_RES;
	}
}

void AdcExecution(ADC_HandleTypeDef* hadc)
{
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
			Raw32ToVolt(adc_buffer, volt_buffer, BUFFER_SIZE);
			buffer_index = 0;
		}
	}
}

void AdcExecution_SingleConversion(ADC_HandleTypeDef* hadc)
{
	HAL_ADC_Start(hadc);
	AdcExecution(hadc);
	HAL_ADC_Stop(hadc);
}

void AdcExecution_HandleCallback(ADC_HandleTypeDef* hadc)
{
	if(buffer_index < BUFFER_SIZE)
	{
		adc_buffer[buffer_index] = HAL_ADC_GetValue(hadc);
		buffer_index++;
	}
	else
	{
		Raw32ToVolt(adc_buffer, volt_buffer, BUFFER_SIZE);
		buffer_index = 0;
	}
}

//lab 7 functions --------------------------
void Raw16ToVolt(uint16_t *pbuf_raw, float* pbuf_float, uint8_t size)
{
	for(int i = 0; i < size; i++)
	{
		pbuf_float[i] = (float)pbuf_raw[i] * ADC_REF / ADC_RES;
	}
}

void AdcStartDma(ADC_HandleTypeDef* hadc, TIM_HandleTypeDef* htim)
{
	HAL_ADC_Start_DMA(hadc, adc_buf, ADC_BUF_LEN);
	HAL_TIM_Base_Start(htim);
}

void SetDataReadyStatus(uint8_t status)
{
	data_ready = status;
}

void AdcHandleMainThread()
{
	if(data_ready)
	{
		Raw16ToVolt(adc_buf_actual, adc_volts, ADC_BUF_LEN);
		SetDataReadyStatus(0);
	}
}

void DataCopyToActualBuffer()
{
	memcpy(adc_buf_actual, adc_buf, ADC_BUF_LEN * sizeof(uint16_t));
}

//#endif
