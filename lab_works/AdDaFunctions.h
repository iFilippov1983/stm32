/*
 * AdDaFunctions.h
 *
 *  Created on: Mar 22, 2026
 *      Author: HYPERPC
 */
#include "main.h"
#include "stm32f1xx_hal.h"

#ifndef ADDAFUNCTIONS_H_
#define ADDAFUNCTIONS_H_

#define BUFFER_SIZE 10
#define TIMEOUT_100 100
#define ADC_RES 4095
#define ADC_REF 3.3

void RawToVolt(uint32_t *pbuf_raw, float* pbuf_float, uint8_t size);
void AdcExecution(ADC_HandleTypeDef* hadc);
void AdcExecution_SingleConversion(ADC_HandleTypeDef* hadc);

#endif /* ADDAFUNCTIONS_H_ */
