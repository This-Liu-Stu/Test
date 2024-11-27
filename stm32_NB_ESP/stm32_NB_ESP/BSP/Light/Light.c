#include "Light.h"

void DRead_Light(int *state)
{
    if(HAL_GPIO_ReadPin(LIGHT_GPIO_Port,LIGHT_Pin) == 1)
        *state = 0;
    else if(HAL_GPIO_ReadPin(LIGHT_GPIO_Port,LIGHT_Pin) == 0)
        *state = 1;
}

void ARead_Light(uint32_t *state)
{
		HAL_ADC_Start(&hadc1);     //启动ADC转换
		*state = HAL_ADC_GetValue(&hadc1);   //获取AD值
}
