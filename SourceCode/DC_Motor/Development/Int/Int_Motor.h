#ifndef __INT_MOTOR_H__
#define __INT_MOTOR_H__

#include "gpio.h"
#include "tim.h"
#include "port.h"
#include "Com_Define.h"


/**
 * @brief ��ʼ�� Motor ���
 * 
 */
void Int_Motor_Init(void);

/**
 * @brief ���� Motor ���
 * 
 */
void Int_Motor_Start(void);

/**
 * @brief ֹͣ Motor ���
 * 
 */
void Int_Motor_Stop(void);

/**
 * @brief ���� Motor ����ٶ�
 * 
 * @param value_speed �ٶ�ֵ����Χ��-490 ~ 490
 * @note ͨ������ PWM ռ�ձ������Ƶ���ٶ�
 */
void Int_Motor_SetSpeed(int16_t value_speed);

#endif /* __INT_MOTOR_H__ */
