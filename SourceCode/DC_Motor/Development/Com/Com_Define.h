#ifndef __COM_DEFINE_H__
#define __COM_DEFINE_H__

#include "main.h"
#include "FreeRTOS.h"
#include "task.h"

// ��ǰ����ģʽ��־
typedef enum
{
    KEY_MODE_MOTOR = 0,
    KEY_MODE_ID,
} Key_MODE;

// ����������ٶ� (0~280)
extern int16_t g_desired_speed;

// �����ʵ�ʲ����ٶ�
extern int16_t g_mesure_speed;

// �����ID (Ĭ��IDΪ1)
extern uint8_t g_motor_id;

// ȫ�ֱ���:��ǰ����ģʽ
extern Key_MODE gs_key_mode;

// ���ƺ���
#define LIMIT(value, min, max) ((value) < (min) ? (min) : ((value) > (max) ? (max) : (value)))

// EEPROM ������
extern TaskHandle_t eeprom_task_handle;

#endif /* __COM_DEFINE_H__ */
