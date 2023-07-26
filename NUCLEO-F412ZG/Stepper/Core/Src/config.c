#include <stdlib.h>

#include "main.h"
#include "config.h"

extern TIM_HandleTypeDef htim3;

void Sysclk_Config(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 8;
	RCC_OscInitStruct.PLL.PLLN = 384;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
	RCC_OscInitStruct.PLL.PLLQ = 8;
	RCC_OscInitStruct.PLL.PLLR = 2;

	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{

	}

	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
	{

	}
}

void GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOG_CLK_ENABLE();

	HAL_GPIO_WritePin(GPIOB, LD1_Pin | LD3_Pin | LD2_Pin, GPIO_PIN_RESET);

	GPIO_InitStruct.Pin = USER_Btn_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(USER_Btn_GPIO_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = LD1_Pin | LD3_Pin | LD2_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

void PWM_Config(STM_HandlesTypeDef* handles)
{
	TIM_MasterConfigTypeDef sMasterConfig = {0};
	TIM_OC_InitTypeDef sConfigOC = {0};

	handles->htim->Instance = TIM3;
	handles->htim->Init.Prescaler = 95;
	handles->htim->Init.CounterMode = TIM_COUNTERMODE_UP;
	handles->htim->Init.Period = 1000;
	handles->htim->Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	handles->htim->Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
//	htim3.Instance = TIM3;
//	htim3.Init.Prescaler = 95;
//	htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
//	htim3.Init.Period = 1000;
//	htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
//	htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

	if (HAL_TIM_PWM_Init(handles->htim) != HAL_OK)
	{
		return;
	}

	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;

	if (HAL_TIMEx_MasterConfigSynchronization(handles->htim, &sMasterConfig) != HAL_OK)
	{
		return;
	}

	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = 0;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

	if (HAL_TIM_PWM_ConfigChannel(handles->htim, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
	{
		return;
	}

	HAL_TIM_MspPostInit(handles->htim);
}

void UART_Config(STM_HandlesTypeDef* handles)
{
	handles->huart->Instance = USART3;
	handles->huart->Init.BaudRate = 115200;
	handles->huart->Init.WordLength = UART_WORDLENGTH_8B;
	handles->huart->Init.StopBits = UART_STOPBITS_1;
	handles->huart->Init.Parity = UART_PARITY_NONE;
	handles->huart->Init.Mode = UART_MODE_TX_RX;
	handles->huart->Init.HwFlowCtl = UART_HWCONTROL_NONE;
	handles->huart->Init.OverSampling = UART_OVERSAMPLING_16;

	if (HAL_UART_Init(&handles->huart) != HAL_OK)
	{

	}
}
