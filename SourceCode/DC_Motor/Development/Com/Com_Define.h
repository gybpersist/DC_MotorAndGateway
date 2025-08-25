#ifndef __COM_DEFINE_H__
#define __COM_DEFINE_H__

#include "main.h"
#include "FreeRTOS.h"
#include "task.h"

// 当前按键模式标志
typedef enum
{
    KEY_MODE_MOTOR = 0,
    KEY_MODE_ID,
} Key_MODE;

// 电机的期望速度 (0~280)
extern int16_t g_desired_speed;

// 电机的实际测量速度
extern int16_t g_mesure_speed;

// 电机的ID (默认ID为1)
extern uint8_t g_motor_id;

// 全局变量:当前按键模式
extern Key_MODE gs_key_mode;

// 限制函数
#define LIMIT(value, min, max) ((value) < (min) ? (min) : ((value) > (max) ? (max) : (value)))

// EEPROM 任务句柄
extern TaskHandle_t eeprom_task_handle;

#endif /* __COM_DEFINE_H__ */
