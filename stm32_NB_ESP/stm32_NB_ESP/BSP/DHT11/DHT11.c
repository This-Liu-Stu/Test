#include "dht11.h"
/*
 * DHT11���ţ�����/���ģʽ���ú��� 
 * Mode = 0/INPUT  ʱ ����ģʽ  
 * Mode = 1/OUTPUT ʱ ���ģʽ  
 */
void DHT11_PIN_Mode(int Mode)
{	
   if(Mode)   
   {
		GPIO_InitTypeDef GPIO_InitStruct = {0};							// ����GPIO_InitTypeDef�ṹ�� 
		GPIO_InitStruct.Pin = DHT11_Pin;                    // ����ѡ��
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;         // ����ģʽ�����ģʽ
		GPIO_InitStruct.Pull = GPIO_NOPULL;                 // �����ڲ�����
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;       // �������ʣ�����
		HAL_GPIO_Init(DHT11_GPIO_Port, &GPIO_InitStruct);
   }
   else
   {
	    GPIO_InitTypeDef GPIO_InitStruct = {0};						// ����GPIO_InitTypeDef�ṹ�� 
		GPIO_InitStruct.Pin = DHT11_Pin;				    				// ����ѡ��
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;							// ����ģʽ������ģʽ
		GPIO_InitStruct.Pull = GPIO_NOPULL;									// �����ڲ�����
		HAL_GPIO_Init(DHT11_GPIO_Port, &GPIO_InitStruct);
   }
}  
 
/*
 *DHT11��ʼ����
 *����DHT11ʱ��ͼ������ҪҪ������ʼ�źţ���Ҫ�����ߵ�ƽ���ͣ�18~30ms��
 */
void DHT11_Start(void)
{
	DHT11_PIN_Mode(OUTPUT);
	DHT11_IO_SET;    				// �������ߴ��ڸߵ�ƽ״̬
	HAL_Delay(1);
	DHT11_IO_RESET;  				// ��������20ms����ʾ����������ʼ�ź�
	HAL_Delay(20);
	DHT11_IO_SET;    				// ���������ߵȴ���������Ӧ
	DHT11_Delay_us(30);
}
 
/**
  * DHT11��Ӧ��⺯��
  * ����1��δ��⵽DHT11�Ĵ���
  * ����0�����ڳ����ɸߵ��͵ı仯����
  */
uint8_t DHT11_Check(void)
{
	uint8_t retry = 0;
	DHT11_PIN_Mode(INPUT);              //�������л�Ϊ����ģʽ
	while(!DHT11_IO_Read && retry<100)  //��Ƭ��������ʼ�źź�DHT11�Ὣ��������83΢��
	{
		retry++;
		DHT11_Delay_us(1);
	}
	if(retry >= 100)return 1;
	else retry = 0;
	
	while(DHT11_IO_Read && retry<100)  //DHT11���ͺ���ٴ�����87΢��
	{
		retry++;
		DHT11_Delay_us(1);
	}
	if(retry >= 100) return 1;
	return 0;
}
 
 
/**
  * ��DHT11��ȡһ��λ
  * ����ֵ��1/0
  */
uint8_t DHT11_Read_Bit(void)
{
	DHT11_PIN_Mode(INPUT);
	while(!DHT11_IO_Read);
	DHT11_Delay_us(40);
	if(DHT11_IO_Read)
	{
		while(DHT11_IO_Read);
		return 1;
	}
	else
	{
		return 0;
	}
}
 
/**
  *  ��ȡһ���ֽ����� 1byte / 8bit
  *  ����ֵ��һ���ֽڵ�����
  */
uint8_t DHT11_Read_Byte(void)
{
    uint8_t i,buf = 0;                             //  ��ʱ�洢����
    
    for(i=0; i<8 ;i++)
    {
        buf <<= 1;                                 
        if(DHT11_Read_Bit())                        //  1byte -> 8bit
        {
            buf |= 1;                              //  0000 0001
        }
    }
    return buf;
}
 
/**
  * ��ȡ��ʪ�ȴ��������� 5byte / 40bit
  * ʹ�÷�������������float��������������ַ���뺯��
  * ע�⣺����ʹ�øú����ļ����Ҫ����2�룬����ᵼ�����ݲ�����׼ȷ
  */
uint8_t data[5] = {0};
 
uint8_t DHT11_READ_DATA(float *temp, float *humi)
{
   uint8_t i;
   DHT11_Start();                                 //  �������������ź�
   
   if(!DHT11_Check())                             //  ���DHT11Ӧ��     
   {  
      for(i=0; i<5; i++)
      {                        
         data[i] = DHT11_Read_Byte();             //  ��ȡ 5byte
      }
      if(data[0] + data[1] + data[2] + data[3] == data[4])
      {
				 *humi = data[0] + 0.1*data[1];
				 *temp = data[2] + 0.1*data[3];
         return 1;                                //  ����У��ͨ��
      }
      else return 0;                              //  ����У��ʧ��
   }
   else return 2;                                 //  ���DHT11��Ӧ��
}
 
/**
  * ΢����ʱ����
  * ȫϵ��ͨ�ã�ֻ��Ҫ���궨��CPU_FREQUENCY_MHZ����ʱ����Ƶ�޸ļ��ɡ�
  * ϵͳ�δ�ʱ����HAL���ʼ���ģ��ұ�����HAL���ʼ����
  */
#define CPU_FREQUENCY_MHZ   (int)(HAL_RCC_GetHCLKFreq()/1000000)		// �Զ���ȡSTM32ʱ����Ƶ
	
void DHT11_Delay_us(__IO uint32_t delay)  
{
    int last, curr, val;
    int temp;
 
    while (delay != 0)
    {
        temp = delay > 900 ? 900 : delay;
        last = SysTick->VAL;
        curr = last - CPU_FREQUENCY_MHZ * temp;
        if (curr >= 0)
        {
            do
            {
                val = SysTick->VAL;
            }
            while ((val < last) && (val >= curr));
        }
        else
        {
            curr += CPU_FREQUENCY_MHZ * 1000;
            do
            {
                val = SysTick->VAL;
            }
            while ((val <= last) || (val > curr));
        }
        delay -= temp;
    }
}
