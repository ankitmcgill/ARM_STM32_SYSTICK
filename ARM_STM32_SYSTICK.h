/////////////////////////////////////////////////////
// ARM - STM32 - SYSTICK LIBRARY
//
// FEBRUARY 26 2017
//
// ANKIT BHATNAGAR
// ANKIT.BHATNAGARINDIA@GMAIL.COM
/////////////////////////////////////////////////////

#ifndef _ARM_STM32_SYSTICK_
#define _ARM_STM32_SYSTICK_

#include <stdint.h>

//CHECK WHAT MCU US BEING USED IN ORDER TO INCLUDE
//THE RIGHT FILE FROM STM SPL
//THE MCU SHOULD BE DEFINED IN TARGET OPTIONS -> C/C++
#ifdef STM32F103
	//SETTINGS SPECIFIC FOR STM32F072 SERIES
	#include "misc.h"
	
	#define DEVICE_UNIQUE_ID_ADDRESS 0x1FFFF7E8
#endif

#ifdef STM32F072 
	//SETTINGS SPECIFIC FOR STM32F072 SERIES
	#include "stm32f0xx_misc.h"
	
	#define DEVICE_UNIQUE_ID_ADDRESS 0x1FFFF7AC
#endif


#define ARM_STM32_SYSTICK_SOURCE_HCLK 			SysTick_CLKSource_HCLK
#define ARM_STM32_SYSTICK_SOURCE_HCLK_DIV8 	SysTick_CLKSource_HCLK_Div8

static uint32_t ARM_STM32_SYSTICK_SOURCE;

void ARM_STM32_SYSTICK_Read_Device_Id(uint32_t* ptr);
void ARM_STM32_SYSTICK_Init(uint32_t systick_clock_source);
void ARM_STM32_SYSTICK_Delay_Us(uint32_t val);
void ARM_STM32_SYSTICK_Delay_Ms(uint32_t val);

#endif
