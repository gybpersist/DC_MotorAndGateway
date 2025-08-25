#ifndef __COM_UTIL_H__
#define __COM_UTIL_H__

#include <stdio.h>
#include "main.h"
#include "time.h"

/**
 * @brief ��ʱ���� us
 * 
 * @param us ��ʱʱ��
 */
void Com_Delay_us(uint16_t us);

/**
 * @brief ��ʱ���� ms
 * 
 * @param ms ��ʱʱ��
 */
void Com_Delay_ms(uint16_t ms);

/**
 * @brief �� UTC ʱ��ת��Ϊ����ʱ��(����ʱ��)
 * 
 * @param utc_time Ҫת���� UTC ʱ��
 * @param local_time ת���õı���ʱ��(����ʱ��)
 * @note ����� utc_time ��ʽΪ "YYYY-MM-DD hh:mm:ss"
 * @note ����� local_time ��ʽΪ "YYYY-MM-DD hh:mm:ss"
 */
void Com_UTC2LocalTime(uint8_t *utc_time, uint8_t *local_time);

// ���� PID �ṹ��
typedef struct
{
    float Kp; // ����ϵ��
    float Ki; // ����ϵ��
    float Kd; // ΢��ϵ��
    
    float dt; // ����ʱ��

    float desired;     // ����ֵ
    float measure;     // ����ֵ

    float integral;    // ������
    float last_error;  // ��һ�ε����
    
    float result;      // PID ������
}PID_Info;

/**
 * @brief PID �㷨
 * 
 * @param pid PID �ṹ��ָ��
 */
void Com_Util_PID(PID_Info *pid);

#endif /* __COM_UTIL_H__ */
