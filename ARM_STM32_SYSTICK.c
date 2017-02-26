/////////////////////////////////////////////////////
// ARM - STM32 - SYSTICK LIBRARY
//
// FEBRUARY 26 2017
//
// ANKIT BHATNAGAR
// ANKIT.BHATNAGARINDIA@GMAIL.COM
/////////////////////////////////////////////////////

#include "ARM_STM32_SYSTICK.h"

uint32_t ARM_STM32_SYSTICK_SOURCE;

void ARM_STM32_SYSTICK_Read_Device_Id(uint32_t* ptr)
{
	//READ AND RETURN 96 BITS (12 BYTES)
	//UNIQUE DEVICE ID
	
	uint32_t* ptr_val = ((uint32_t*)DEVICE_UNIQUE_ID_ADDRESS);
	
	ptr[0] = ptr_val[0];
	ptr[1] = ptr_val[1];
	ptr[2] = ptr_val[2];
}

void ARM_STM32_SYSTICK_Init(uint32_t systick_clock_source)
{
	//SET THE SOURCE OF SYSTICK (HCLK OR HCLK/8)
	SysTick_CLKSourceConfig(systick_clock_source);
	
	ARM_STM32_SYSTICK_SOURCE = systick_clock_source;
}

void ARM_STM32_SYSTICK_Delay_Us(uint32_t val)
{
	//BLOCKING DELAY OF SPECIFIED MICRO-SECONDS
	
	RCC_ClocksTypeDef clock;
	RCC_GetClocksFreq(&clock);
	
	//FIND THE SYSTICK COUNT REQUIRED FOR 1US PERIOD
	uint32_t one_us_count;
	if(ARM_STM32_SYSTICK_SOURCE == SysTick_CLKSource_HCLK)
	{
		one_us_count = (clock.HCLK_Frequency/1000000);
	}
	else
	{
		one_us_count = (clock.HCLK_Frequency/8000000);
	}
	
	SysTick->VAL=0;
	SysTick->LOAD = one_us_count;
	SysTick->CTRL &= ~(SysTick_CTRL_TICKINT_Msk);
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
	
	while(val != 0)
	{
		while((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == 0){};
		val--;
	}
	
	//SYSTICK TIME DONE. DISABLE IT
	SysTick->CTRL &= ~(SysTick_CTRL_ENABLE_Msk);
}

void ARM_STM32_SYSTICK_Delay_Ms(uint32_t val)
{
	//BLOCKING DELAY OF SPECIFIED MILLI-SECONDS
	
	ARM_STM32_SYSTICK_Delay_Us(val * 1000);
}

