//#ifdef HAL_ADC_MODULE_ENABLED
#include <string.h>
#include "main.h"
#include "stm32f1xx_hal.h"

#ifndef ADDAFUNCTIONS_H_
#define ADDAFUNCTIONS_H_

#define BUFFER_SIZE 100
#define TIMEOUT_100 100
#define ADC_RES 4095.0f
#define ADC_REF 3.3f
#define ADC_BUF_LEN 200

//lab 5 functions --------------------------
void Raw32ToVolt(uint32_t *pbuf_raw, float* pbuf_float, uint8_t size);
void AdcExecution(ADC_HandleTypeDef* hadc);
void AdcExecution_SingleConversion(ADC_HandleTypeDef* hadc);
void AdcExecution_HandleCallback(ADC_HandleTypeDef* hadc);

//lab 7 functions --------------------------
void Raw16ToVolt(uint16_t *pbuf_raw, float* pbuf_float, uint8_t size);
void AdcStartDma(ADC_HandleTypeDef* hadc, TIM_HandleTypeDef* htim);
void SetDataReadyStatus(uint8_t status);
void AdcHandleMainThread();
void DataCopyToActualBuffer();

#endif /* ADDAFUNCTIONS_H_ */

//#endif
