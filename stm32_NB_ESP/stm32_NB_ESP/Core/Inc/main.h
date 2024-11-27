/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
#define RXBUFFERSIZE  4096     //�������ֽ���

#define USART3_RX_EN 			1					//0,������;1,����.

extern uint8_t  USART3_RX_BUF[RXBUFFERSIZE]; 		//���ջ���,���USART3_MAX_RECV_LEN�ֽ�
extern uint16_t USART3_RX_STA;   						//��������״̬
extern int LED;					//LED״̬λ 1-8 ��ˮ�� 	0Ϩ��
extern int LED_state;			//0�ر�	1����
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define DHT11_Pin GPIO_PIN_2
#define DHT11_GPIO_Port GPIOC
#define LIGHT_Pin GPIO_PIN_1
#define LIGHT_GPIO_Port GPIOA
#define FUN_Pin GPIO_PIN_4
#define FUN_GPIO_Port GPIOA
#define LED1_Pin GPIO_PIN_6
#define LED1_GPIO_Port GPIOA
#define LED2_Pin GPIO_PIN_7
#define LED2_GPIO_Port GPIOA
#define LED4_Pin GPIO_PIN_7
#define LED4_GPIO_Port GPIOC
#define LED6_Pin GPIO_PIN_8
#define LED6_GPIO_Port GPIOA
#define LED5_Pin GPIO_PIN_9
#define LED5_GPIO_Port GPIOA
#define LED7_Pin GPIO_PIN_4
#define LED7_GPIO_Port GPIOB
#define LED8_Pin GPIO_PIN_5
#define LED8_GPIO_Port GPIOB
#define LED3_Pin GPIO_PIN_6
#define LED3_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
