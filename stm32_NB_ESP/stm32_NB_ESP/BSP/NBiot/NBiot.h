#ifndef _NBIOT_H_
#define _NBIOT_H_

#include "main.h"
#include "usart.h"

/*MQTT ���Ӳ���*/
#define clientId "k1dptvQQkqa.BC26|securemode=2,signmethod=hmacsha256,timestamp=1728374215514|"; // MQTT���Ӳ����пͻ���ID
#define username "BC26&k1dptvQQkqa"; // MQTT���Ӳ������û���
#define  passwd "7bae9cedf34dd239ecc87c2e1a776ac009a45cffdc385fdbca44a533671ca6c4"; // MQTT���Ӳ�������Կ

#define  MQTCONNPAR String("AT+QMTCONN=0,\"") + clientId + "\",\"" + username + "\",\"" + passwd + "\"";

void NBiot_Init(void);
void NBiot_Send(char *property,int Data);
uint8_t NBiot_send_cmd(char *cmd,char *ack,uint16_t waittime);
uint8_t* NBiot_check_cmd(char *str);

#endif

