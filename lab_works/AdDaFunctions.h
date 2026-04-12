#ifdef HAL_ADC_MODULE_ENABLED

#include "main.h"
#include "stm32f1xx_hal.h"

#ifndef ADDAFUNCTIONS_H_
#define ADDAFUNCTIONS_H_

#define BUFFER_SIZE 100
#define TIMEOUT_100 100
#define ADC_RES 4095
#define ADC_REF 3.3f

void RawToVolt(uint32_t *pbuf_raw, float* pbuf_float, uint8_t size);
void AdcExecution(ADC_HandleTypeDef* hadc);
void AdcExecution_SingleConversion(ADC_HandleTypeDef* hadc);
void AdcExecution_HandleCallback(ADC_HandleTypeDef* hadc);

#endif /* ADDAFUNCTIONS_H_ */

#endif
