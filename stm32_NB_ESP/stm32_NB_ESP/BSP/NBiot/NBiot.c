#include "NBiot.h"
#include "usart.h"
#include "string.h"

/*****************************************************
*函数名称：void NBiot_Init(void)
*函数功能：NBiot参数初始化
*入口参数：void
*出口参数：void
*****************************************************/
void NBiot_Init(void)
{
	//AT指令
	NBiot_send_cmd("AT","OK",50);	//配置WiFi工作模式为Station模式:就是NBiot模块去连接自己家的wifi,
															//手机也连接自己家的wifi然后实现了手机和WiFi模块的通信,(自己家wifi相当于一个中介)
	//读取SIM卡
	NBiot_send_cmd("AT+CPIN?","+CPIN: READY",20);
	HAL_Delay(1000);
	
	//建立服务器的IP和端口连接,139.196.135.135，必须用这个，此处不需要更改
	NBiot_send_cmd("AT+QMTOPEN=0,\"139.196.135.135\",1883","W+QMTOPEN: 0,0",300);
	HAL_Delay(50);
	
//	//AT+MQTTUSERCFG - 配置 MQTT 用户属性
//	NBiot_send_cmd(MQTCONNPAR,"OK",100);
//	HAL_Delay(50);
//	//配置 MQTT 客户端 ID
//	NBiot_send_cmd(MQTT_Client,"OK",100);
//	HAL_Delay(50);
//	//连接指定 MQTT协议
//	NBiot_send_cmd(MQTT_Pass,"OK",300);
	
	HAL_Delay(50);
}

/*****************************************************
*函数名称：uint8_t NBiot_send_cmd(char *cmd,char *ack,uint16_t waittime)
*函数功能：向NBiot发送命令
*入口参数：cmd:发送的命令字符串;ack:期待的应答结果,如果为空,则表示不需要等待应答;waittime:等待时间(单位:10ms)
*出口参数：0,发送成功(得到了期待的应答结果);1,发送失败
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
*函数名称：uint8_t* NBiot_check_cmd(char *str)
*函数功能：向NBiot发送命令
*入口参数：str:期待的应答结果
*出口参数：0,没有得到期待的应答结果;其他,期待应答结果的位置(str的位置)
*****************************************************/
uint8_t* NBiot_check_cmd(char *str)
{
	char *strx=0;
	if(USART3_RX_STA&0X8000)		//接收到一次数据了
	{ 
		USART3_RX_BUF[USART3_RX_STA&0X7FFF]=0;//添加结束符
		strx=strstr((const char*)USART3_RX_BUF,(const char*)str);
	} 
	return (uint8_t*)strx;
}

/*****************************************************
*函数名称：NBiot_Send(char *property,int Data)
*函数功能：向云端发送数据
*入口参数：char *property,int Data （属性）（数据）
*出口参数：void
*****************************************************/
void NBiot_Send(char *property,int Data)
{
	USART3_RX_STA=0;
//	USART3_Send("AT+MQTTPUB=0,\"%s\",\"{\\\"params\\\":{\\\"%s\\\":%d}}\",1,0\r\n",post,property,Data);
}
