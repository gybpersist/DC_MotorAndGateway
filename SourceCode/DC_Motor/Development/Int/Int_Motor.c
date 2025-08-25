#include "Int_Motor.h"

void Int_Motor_Init(void)
{
    // ��ʼ�� PWM �� PWMN 
    HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
    HAL_TIMEx_PWMN_Start(&htim1,TIM_CHANNEL_1);
}

/**
 * @brief ���� Motor ���
 * 
 */
void Int_Motor_Start(void)
{
    // ����Ȧ[2]���а�
    REG_COILS_BUF[2] = 1;
    // ���� SHUTDOWN ����
    HAL_GPIO_WritePin(SHUTDOWN_GPIO_Port,SHUTDOWN_Pin,GPIO_PIN_RESET);
}

/**
 * @brief ֹͣ Motor ���
 * 
 */
void Int_Motor_Stop(void)
{
    // ����Ȧ[2]���а�
    REG_COILS_BUF[2] = 0;
    // �������ٶ�Ҳ����Ϊ0
    g_desired_speed = 0;
    // ���� SHUTDOWN ����
    HAL_GPIO_WritePin(SHUTDOWN_GPIO_Port,SHUTDOWN_Pin,GPIO_PIN_SET);
}

/**
 * @brief ���� Motor ����ٶ�
 * 
 * @param speed �ٶ�ֵ����Χ��-490 ~ 490
 * @note ͨ������ PWM ռ�ձ������Ƶ���ٶ�
 */
void Int_Motor_SetSpeed(int16_t value_speed)
{
    __HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_1,value_speed + 500);
}


