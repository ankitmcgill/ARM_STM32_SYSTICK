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
#include <stdio.h>
#include <stdbool.h>
#include "misc.h"

#define ARM_STM32_SYSTICK_SOURCE_HCLK 			SysTick_CLKSource_HCLK
#define ARM_STM32_SYSTICK_SOURCE_HCLK_DIV8 		SysTick_CLKSource_HCLK_Div8

void ARM_STM32_SYSTICK_Init(uint32_t systick_clock_source);
void ARM_STM32_SYSTICK_Delay_Blocking_Us(uint32_t val);
void ARM_STM32_SYSTICK_Delay_Blocking_Ms(uint32_t val);

#endif
