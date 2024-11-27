#include "main.h"
 
#ifndef __DHT11_H_
#define __DHT11_H_
 
#define DHT11_IO_Read   HAL_GPIO_ReadPin(DHT11_GPIO_Port,DHT11_Pin)                   //��DHT11���ŵ�ƽ
#define DHT11_IO_SET    HAL_GPIO_WritePin(DHT11_GPIO_Port,DHT11_Pin,GPIO_PIN_SET)     //DHT11�����øߵ�ƽ
#define DHT11_IO_RESET  HAL_GPIO_WritePin(DHT11_GPIO_Port,DHT11_Pin,GPIO_PIN_RESET)   //DHT11�����õ͵�ƽ
  
#define INPUT 0   //��������ģʽ
#define OUTPUT 1  //�������ģʽ
 
void DHT11_Delay_us(__IO uint32_t delay);           // ΢���ʱ����
void DHT11_PIN_Mode(int Mode);  										// ����ģʽ���ú���
void DHT11_Start(void);         										// ��ʼ�źŷ��ͺ���
uint8_t DHT11_Check(void);      										// DHT11Ӧ���⺯��
uint8_t DHT11_Read_Bit(void);   										// ��ȡһ������λ��bit����8 bit = 1 byte
uint8_t DHT11_Read_Byte(void);  										// ��ȡһ���ֽڵ�����
uint8_t DHT11_READ_DATA(float *temp, float *humi);  // ��ʪ�����ݶ�ȡ����
 
#endif
