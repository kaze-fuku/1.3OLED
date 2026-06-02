/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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
#include "i2c.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "oled.h"
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
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
  OLED_Init();
  OLED_SetCursor(5, 6);
  OLED_WriteString("OLED OK!", &Font_8x16, 1);
  HAL_Delay(1500);
  OLED_Clear();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* ---- Demo: 8x16 big text ---- */
    OLED_Clear();
    OLED_SetCursor(0, 0);
    OLED_WriteString("Hello World!", &Font_8x16, 1);
    HAL_Delay(2000);

    /* ---- Demo: 6x8 small text ---- */
    
    OLED_Clear();
    OLED_SetCursor(0, 0);
    OLED_WriteString("ABCDEFGHIJKLMNOPQRST", &Font_6x8, 1);
    OLED_SetCursor(0, 10);
    OLED_WriteString("UVWXYZ abcdefghijklm", &Font_6x8, 1);
    OLED_SetCursor(0, 20);
    OLED_WriteString("nopqrstuvwxyz 01234", &Font_6x8, 1);
    OLED_SetCursor(0, 30);
    OLED_WriteString("56789 !@#$%^&*()_+-", &Font_6x8, 1);
    OLED_SetCursor(0, 40);
    OLED_WriteString("=[]{}|;:,.<>/?~", &Font_6x8, 1);
    HAL_Delay(3000);

    /* ---- Demo: mix both fonts ---- */


    //123ceshi
    OLED_Clear();
    OLED_SetCursor(0, 0);
    OLED_WriteString("STM32", &Font_8x16, 1);
    OLED_SetCursor(0, 20);
    OLED_WriteString("F103C8T6 @ 72MHz", &Font_6x8, 1);
    OLED_SetCursor(0, 32);
    OLED_WriteString("SSD1306 128x64 OLED", &Font_6x8, 1);
    OLED_SetCursor(0, 44);
    OLED_WriteString("I2C HAL Driver OK!", &Font_6x8, 1);
    HAL_Delay(3000);

    /* ---- Demo: invert and contrast ---- */
    OLED_Clear();
    OLED_SetCursor(0, 6);
    OLED_WriteString("Invert Demo", &Font_8x16, 1);
    HAL_Delay(1000);
    OLED_Invert(1);
    HAL_Delay(1000);
    OLED_Invert(0);
    HAL_Delay(1000);

    OLED_SetContrast(0x00); HAL_Delay(300);
    OLED_SetContrast(0x7F); HAL_Delay(300);
    OLED_SetContrast(0xFF); HAL_Delay(300);
    OLED_SetContrast(0x7F);
  }
  /* USER CODE END WHILE */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
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

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

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
