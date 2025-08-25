#ifndef __APP_MOTOR_H__
#define __APP_MOTOR_H__

#include "Int_Motor.h"
#include "Com_Define.h"
#include "Com_Debug.h"
#include "Com_Util.h"

/**
 * @brief ��ʼ�� Motor ���
 * 
 */
void App_Motor_Init(void);

/**
 * @brief ��ȡ Motor ������з���
 * 
 * @return int8_t ������з��� -1 ������ 1 ������
 */
int8_t App_Motor_GetDir(void);

/**
 * @brief ��ȡ Motor ��� mesure_speedת��
 * 
 * @param dt ʱ���� ��λ����
 * @note ��������ѯ dt ʱ�����ڵ���
 */
void App_Motor_GetSpeed(float dt);

/**
 * @brief ���� Motor ���
 * 
 * @param dt ʱ���� ��λ����
 * @note ��������ѯ dt ʱ�����ڵ���
 */
void App_Motor_Run(float dt);

/**
 * @brief ���� modbus ���� 
 * 
 * @note ʹ�� modbus , ���� modbus ����, ����������ִ�� �򿪺͹رյ��
 */
void App_Motor_CheckModbus(void);


#endif /* __APP_MOTOR_H__ */
