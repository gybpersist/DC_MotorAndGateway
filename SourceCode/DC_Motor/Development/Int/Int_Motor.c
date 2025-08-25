#include "Int_Motor.h"

void Int_Motor_Init(void)
{
    // 初始化 PWM 和 PWMN 
    HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
    HAL_TIMEx_PWMN_Start(&htim1,TIM_CHANNEL_1);
}

/**
 * @brief 启动 Motor 电机
 * 
 */
void Int_Motor_Start(void)
{
    // 和线圈[2]进行绑定
    REG_COILS_BUF[2] = 1;
    // 拉低 SHUTDOWN 引脚
    HAL_GPIO_WritePin(SHUTDOWN_GPIO_Port,SHUTDOWN_Pin,GPIO_PIN_RESET);
}

/**
 * @brief 停止 Motor 电机
 * 
 */
void Int_Motor_Stop(void)
{
    // 和线圈[2]进行绑定
    REG_COILS_BUF[2] = 0;
    // 把期望速度也设置为0
    g_desired_speed = 0;
    // 拉高 SHUTDOWN 引脚
    HAL_GPIO_WritePin(SHUTDOWN_GPIO_Port,SHUTDOWN_Pin,GPIO_PIN_SET);
}

/**
 * @brief 设置 Motor 电机速度
 * 
 * @param speed 速度值，范围：-490 ~ 490
 * @note 通过设置 PWM 占空比来控制电机速度
 */
void Int_Motor_SetSpeed(int16_t value_speed)
{
    __HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_1,value_speed + 500);
}


