#include "Com_Define.h"

// 全局变量:电机的期望速度 (0~280)
int16_t g_desired_speed = 0;

// 全局变量:电机的实际测量速度
int16_t g_mesure_speed = 0;

// 全局变量:电机的ID (默认ID为1)
uint8_t g_motor_id = 1;

// 全局变量:当前按键模式
Key_MODE gs_key_mode = KEY_MODE_MOTOR;
