#ifndef __INT_MOTOR_H__
#define __INT_MOTOR_H__

#include "gpio.h"
#include "tim.h"
#include "port.h"
#include "Com_Define.h"


/**
 * @brief 初始化 Motor 电机
 * 
 */
void Int_Motor_Init(void);

/**
 * @brief 启动 Motor 电机
 * 
 */
void Int_Motor_Start(void);

/**
 * @brief 停止 Motor 电机
 * 
 */
void Int_Motor_Stop(void);

/**
 * @brief 设置 Motor 电机速度
 * 
 * @param value_speed 速度值，范围：-490 ~ 490
 * @note 通过设置 PWM 占空比来控制电机速度
 */
void Int_Motor_SetSpeed(int16_t value_speed);

#endif /* __INT_MOTOR_H__ */
