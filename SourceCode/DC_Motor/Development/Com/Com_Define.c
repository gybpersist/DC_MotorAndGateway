#include "Com_Define.h"

// ȫ�ֱ���:����������ٶ� (0~280)
int16_t g_desired_speed = 0;

// ȫ�ֱ���:�����ʵ�ʲ����ٶ�
int16_t g_mesure_speed = 0;

// ȫ�ֱ���:�����ID (Ĭ��IDΪ1)
uint8_t g_motor_id = 1;

// ȫ�ֱ���:��ǰ����ģʽ
Key_MODE gs_key_mode = KEY_MODE_MOTOR;
