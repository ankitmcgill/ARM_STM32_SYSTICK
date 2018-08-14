/////////////////////////////////////////////////////
// ARM - STM32 - SYSTICK LIBRARY
//
// FEBRUARY 26 2017
//
// ANKIT BHATNAGAR
// ANKIT.BHATNAGARINDIA@GMAIL.COM
/////////////////////////////////////////////////////

#include "ARM_STM32_SYSTICK.h"

static bool s_initialized = false;
static uint32_t s_systick_clk_source;

void ARM_STM32_SYSTICK_Init(uint32_t systick_clock_source)
{
	//SET THE SOURCE OF SYSTICK (HCLK OR HCLK/8)

	if(s_initialized)
	{
		//ALREADY INITIALIZED
		return;
	}

	SysTick_CLKSourceConfig(systick_clock_source);
	s_systick_clk_source = systick_clock_source;

	s_initialized = true;
}

void ARM_STM32_SYSTICK_Delay_Blocking_Us(uint32_t val)
{
	//BLOCKING DELAY OF SPECIFIED MICRO-SECONDS
	
	RCC_ClocksTypeDef clock;
	RCC_GetClocksFreq(&clock);
	
	//FIND THE SYSTICK COUNT REQUIRED FOR 1US PERIOD
	uint32_t one_us_count;
	if(s_systick_clk_source == SysTick_CLKSource_HCLK)
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

void ARM_STM32_SYSTICK_Delay_Blocking_Ms(uint32_t val)
{
	//BLOCKING DELAY OF SPECIFIED MILLI-SECONDS
	
	ARM_STM32_SYSTICK_Delay_Blocking_Us(val * 1000);
}

