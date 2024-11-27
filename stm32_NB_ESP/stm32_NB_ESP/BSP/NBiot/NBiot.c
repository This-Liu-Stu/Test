#include "NBiot.h"
#include "usart.h"
#include "string.h"

/*****************************************************
*�������ƣ�void NBiot_Init(void)
*�������ܣ�NBiot������ʼ��
*��ڲ�����void
*���ڲ�����void
*****************************************************/
void NBiot_Init(void)
{
	//ATָ��
	NBiot_send_cmd("AT","OK",50);	//����WiFi����ģʽΪStationģʽ:����NBiotģ��ȥ�����Լ��ҵ�wifi,
															//�ֻ�Ҳ�����Լ��ҵ�wifiȻ��ʵ�����ֻ���WiFiģ���ͨ��,(�Լ���wifi�൱��һ���н�)
	//��ȡSIM��
	NBiot_send_cmd("AT+CPIN?","+CPIN: READY",20);
	HAL_Delay(1000);
	
	//������������IP�Ͷ˿�����,139.196.135.135��������������˴�����Ҫ����
	NBiot_send_cmd("AT+QMTOPEN=0,\"139.196.135.135\",1883","W+QMTOPEN: 0,0",300);
	HAL_Delay(50);
	
//	//AT+MQTTUSERCFG - ���� MQTT �û�����
//	NBiot_send_cmd(MQTCONNPAR,"OK",100);
//	HAL_Delay(50);
//	//���� MQTT �ͻ��� ID
//	NBiot_send_cmd(MQTT_Client,"OK",100);
//	HAL_Delay(50);
//	//����ָ�� MQTTЭ��
//	NBiot_send_cmd(MQTT_Pass,"OK",300);
	
	HAL_Delay(50);
}

/*****************************************************
*�������ƣ�uint8_t NBiot_send_cmd(char *cmd,char *ack,uint16_t waittime)
*�������ܣ���NBiot��������
*��ڲ�����cmd:���͵������ַ���;ack:�ڴ���Ӧ����,���Ϊ��,���ʾ����Ҫ�ȴ�Ӧ��;waittime:�ȴ�ʱ��(��λ:10ms)
*���ڲ�����0,���ͳɹ�(�õ����ڴ���Ӧ����);1,����ʧ��
*****************************************************/
uint8_t NBiot_send_cmd(char *cmd,char *ack,uint16_t waittime)
{
	uint8_t res=0; 
	USART3_RX_STA=0;
	USART3_Send("%s\r\n",cmd);
	if(ack&&waittime)		
	{
		while(--waittime)	
		{
			HAL_Delay(10);
			if(USART3_RX_STA&0X8000)
			{
				if(NBiot_check_cmd(ack))
				{
					//printf("ack:%s\r\n",(u8*)ack);
					break;
				}
					USART3_RX_STA=0;
			}
		}
		if(waittime==0)res=1; 
	}
	return res;
} 

/*****************************************************
*�������ƣ�uint8_t* NBiot_check_cmd(char *str)
*�������ܣ���NBiot��������
*��ڲ�����str:�ڴ���Ӧ����
*���ڲ�����0,û�еõ��ڴ���Ӧ����;����,�ڴ�Ӧ������λ��(str��λ��)
*****************************************************/
uint8_t* NBiot_check_cmd(char *str)
{
	char *strx=0;
	if(USART3_RX_STA&0X8000)		//���յ�һ��������
	{ 
		USART3_RX_BUF[USART3_RX_STA&0X7FFF]=0;//��ӽ�����
		strx=strstr((const char*)USART3_RX_BUF,(const char*)str);
	} 
	return (uint8_t*)strx;
}

/*****************************************************
*�������ƣ�NBiot_Send(char *property,int Data)
*�������ܣ����ƶ˷�������
*��ڲ�����char *property,int Data �����ԣ������ݣ�
*���ڲ�����void
*****************************************************/
void NBiot_Send(char *property,int Data)
{
	USART3_RX_STA=0;
//	USART3_Send("AT+MQTTPUB=0,\"%s\",\"{\\\"params\\\":{\\\"%s\\\":%d}}\",1,0\r\n",post,property,Data);
}
