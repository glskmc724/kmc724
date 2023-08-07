#include "main.h"
#include "stm32f4xx_it.h"
#include "config.h"

extern STM_HandlesTypeDef handles;

void NMI_Handler(void)
{
	while (1)
	{

	}
}

void HardFault_Handler(void)
{
	while (1)
	{

	}
}

void MemManage_Handler(void)
{
	while (1)
	{

	}
}

void BusFault_Handler(void)
{
	while (1)
	{

	}
}

void UsageFault_Handler(void)
{
	while (1)
	{

	}
}

void SVC_Handler(void)
{

}

void DebugMon_Handler(void)
{

}

void PendSV_Handler(void)
{

}

void SysTick_Handler(void)
{
	HAL_IncTick();
}

void TIM3_IRQHandler(void)
{
	HAL_TIM_IRQHandler(handles.htim);
}

void EXTI15_10_IRQHandler(void)
{
	HAL_GPIO_EXTI_IRQHandler(BLUE_BTN_Pin);
}
