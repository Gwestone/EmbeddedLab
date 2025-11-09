/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

#include <stdio.h>

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

void vApplicationStackOverflowHook(TaskHandle_t xTask, char* text) {
  while (1){}
}

void vApplicationMallocFailedHook(void) {
  while(1) {
    HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
    for(volatile int i=0; i<500000; i++);
  }
}

void YUSH_periodic_1(void *pvParameters) {
  const TickType_t T1 = pdMS_TO_TICKS(140);
  const TickType_t C1 = pdMS_TO_TICKS(30);
  TickType_t xLastWakeTime = xTaskGetTickCount();

  char buffer[64];

  for (;;) {
    TickType_t beforeDelay = xTaskGetTickCount();
    xTaskDelayUntil(&xLastWakeTime, T1);
    TickType_t afterDelay = xTaskGetTickCount();

    if ((long)(afterDelay - xLastWakeTime) > 0) {
      snprintf(buffer, sizeof(buffer), "1s: expected=%lu, actual=%lu, diff=%ld\n",
          (unsigned long)xLastWakeTime,
          (unsigned long)afterDelay,
          (long)(afterDelay - xLastWakeTime));
      printRTT(buffer);
    }

    vTaskDelay(C1);
    //printRTT("1f\n");
  }
}

void YUSH_periodic_2(void *pvParameters) {

  //T2 = 21 + (1 mod 5) ms = 22 ms;
  int T2 = pdMS_TO_TICKS(22);
  //C2 = 3 + ((ID/3) mod 3) ms = 4 ms;
  int C2 = pdMS_TO_TICKS(4);
  TickType_t xLastWakeTime = xTaskGetTickCount();

  char buffer[64];

  for (;;) {
    TickType_t beforeDelay = xTaskGetTickCount();
    xTaskDelayUntil(&xLastWakeTime, T2);
    TickType_t afterDelay = xTaskGetTickCount();

    if ((long)(afterDelay - xLastWakeTime) > 0) {
      snprintf(buffer, sizeof(buffer), "2s: expected=%lu, actual=%lu, diff=%ld\n",
          (unsigned long)xLastWakeTime,
          (unsigned long)afterDelay,
          (long)(afterDelay - xLastWakeTime));
      printRTT(buffer);
    }

    vTaskDelay(C2);
    //printRTT("1f\n");
  }
}

void YUSH_periodic_3(void *pvParameters) {

  //T3 = 34 + (1 mod 9) ms = 35 ms;
  int T3 = pdMS_TO_TICKS(35);
  //C3 = 4 + ((ID/5) mod 3) ms = 5 ms;
  int C3 = pdMS_TO_TICKS(5);
  TickType_t xLastWakeTime = xTaskGetTickCount();

  char buffer[64];

  for (;;) {
    TickType_t beforeDelay = xTaskGetTickCount();
    xTaskDelayUntil(&xLastWakeTime, T3);
    TickType_t afterDelay = xTaskGetTickCount();

    if ((long)(afterDelay - xLastWakeTime) > 0) {
      snprintf(buffer, sizeof(buffer), "3s: expected=%lu, actual=%lu, diff=%ld\n",
          (unsigned long)xLastWakeTime,
          (unsigned long)afterDelay,
          (long)(afterDelay - xLastWakeTime));
      printRTT(buffer);
    }

    vTaskDelay(C3);
    //printRTT("1f\n");
  }
}


/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */
  uint32_t cpuFreq = HAL_RCC_GetHCLKFreq();
  SEGGER_RTT_printf(0, "CPU Frequency: %lu Hz\n", cpuFreq);
  //Priority 1 mod 2 != 0 -> T2 > T1 > T3
  xTaskCreate(YUSH_periodic_1, "periodic 1", 128, NULL, configMAX_PRIORITIES - 2, NULL);
  xTaskCreate(YUSH_periodic_2, "periodic 2", 256, NULL, configMAX_PRIORITIES - 1, NULL);
  xTaskCreate(YUSH_periodic_3, "periodic 3", 128, NULL, configMAX_PRIORITIES - 3, NULL);
  vTaskStartScheduler();
  Error_Handler();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    // Test LED blinks BEFORE FreeRTOS
    /*for(int i=0; i<5; i++) {
      HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
      HAL_Delay(200);
    }*/

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 12;
  RCC_OscInitStruct.PLL.PLLN = 96;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM5 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM5)
  {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
