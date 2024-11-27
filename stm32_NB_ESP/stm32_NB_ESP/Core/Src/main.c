/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "adc.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "oled.h"
#include "DHT11.h"
#include "Light.h"
#include "LED.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
//串口1配置-串口调试缓存区
int8_t RxBuffer1[RXBUFFERSIZE]; 
uint8_t Uart1_Rx_Cnt = 0;
uint8_t aRxBuffer1;

//串口2配置-NB-iot缓存区
int8_t RxBuffer2[RXBUFFERSIZE];   //接收数据
uint8_t Uart2_Rx_Cnt = 0;
uint8_t aRxBuffer2;

//串口3配置-ESP8266缓存区
int8_t RxBuffer3[RXBUFFERSIZE];   //接收数据
uint8_t Uart3_Rx_Cnt = 0;
uint8_t aRxBuffer3;

__align(8) uint8_t USART3_TX_BUF[RXBUFFERSIZE]; 	//发送缓冲,最大USART2_MAX_SEND_LEN字节 
uint8_t USART3_RX_BUF[RXBUFFERSIZE]; 				//接收缓冲,最大USART2_MAX_RECV_LEN个字节.
uint16_t USART3_RX_STA = 0;

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
float Humi,Temp;				//温湿度缓存位
int Light_D = 0;				//光敏数字量-0暗-1亮
uint32_t Light_A = 0;	//光敏模拟量
int LED = 0;					//LED状态位 1-8 流水灯 	0熄灭
int LED_state = 0;			//0关闭	1开启
uint16_t time1_num = 0;		//Time1定时
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
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_USART3_UART_Init();
  MX_I2C1_Init();
  MX_ADC1_Init();
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */
	HAL_ADCEx_Calibration_Start(&hadc1, ADC_SINGLE_ENDED);    //AD校准
	HAL_TIM_Base_Start_IT(&htim1); // 开启中断
	//串口开启接收中断
	HAL_UART_Receive_IT(&huart1, &aRxBuffer1, 1);	
	HAL_UART_Receive_IT(&huart2, &aRxBuffer2, 1);
	HAL_UART_Receive_IT(&huart3, &aRxBuffer3, 1);
	
//	OLED_Init();                          //OLED初始化
// 	OLED_Clear();                         //先清屏
//	HAL_Delay(1000);
//	OLED_ShowCHinese(25,0,0);  				//在屏幕上方显示“此乃刘同学”             
//	OLED_ShowCHinese(41,0,1);
//	OLED_ShowCHinese(57,0,2);
//	OLED_ShowCHinese(73,0,3);
//	OLED_ShowCHinese(89,0,4);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {	
//		DHT11_READ_DATA(&Temp,&Humi);				//读取温湿度
//		sprintf(DHT11_TX,"Temp:%0.1f ",Temp);
//		DRead_Light(&Light_D);					//获取光敏的数字量值
//		ARead_Light(&Light_A);					//获取光敏的模拟量值
//		HAL_GPIO_WritePin(FUN_GPIO_Port, FUN_Pin, GPIO_PIN_RESET);			//风扇为低电平
//		HAL_GPIO_WritePin(FUN_GPIO_Port, FUN_Pin, GPIO_PIN_SET);				//风扇为高电平
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
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV4;
  RCC_OscInitStruct.PLL.PLLN = 85;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
		if(htim->Instance == TIM1){     
        time1_num++;
    }
		LED++;
		if(LED == 9) LED = 0;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	
    if (huart->Instance == USART1)
    {
        if (Uart1_Rx_Cnt > RXBUFFERSIZE - 2)  // Overflow check
        {
            Uart1_Rx_Cnt = 0;
            memset(RxBuffer1, 0x00, sizeof(RxBuffer1));
        }
        else
        {
            RxBuffer1[Uart1_Rx_Cnt++] = aRxBuffer1;   // Store received data

             // 检查是否接收到结束符（例如换行符和回车符）
            if ((Uart1_Rx_Cnt > 1) && (RxBuffer1[Uart1_Rx_Cnt - 1] == 0x0A) && (RxBuffer1[Uart1_Rx_Cnt - 2] == 0x0D)) // End of data check
            {
                // 输出接收到的完整数据
                HAL_UART_Transmit(&huart1, (uint8_t *)RxBuffer1, Uart1_Rx_Cnt, HAL_MAX_DELAY);
                Uart1_Rx_Cnt = 0;
                memset(RxBuffer1, 0x00, sizeof(RxBuffer1)); // Clear buffer
            }
        }
        HAL_UART_Receive_IT(&huart1, &aRxBuffer1, 1);
    }
    else if (huart->Instance == USART2)
    {
        //
    }
		else  if (huart->Instance == USART3)
    {
        if (Uart3_Rx_Cnt < RXBUFFERSIZE - 1)  
        {
            RxBuffer3[Uart3_Rx_Cnt++] = aRxBuffer3;

            // Check for end of message (newline character)
            if (RxBuffer3[Uart3_Rx_Cnt - 1] == 0x0A) 
            {
								const char *start;

								// 提取 Wind 值
								start = strstr((const char *)RxBuffer3, "\"LED\":"); // 转换为 const char *
								if (start) {
										start = strstr(start, "\"value\":");
										if (start) {
												start += strlen("\"value\":");
												LED = strtol(start, (char **)&start, 10); 
												//做操作
										}
								}
														
                // Reset the buffer after processing
                Uart3_Rx_Cnt = 0;
                memset(RxBuffer3, 0x00, sizeof(RxBuffer3));
            }
        }
        HAL_UART_Receive_IT(&huart3, &aRxBuffer3, 1);  // Re-enable interrupt for next byte
    }

}
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

#ifdef  USE_FULL_ASSERT
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

