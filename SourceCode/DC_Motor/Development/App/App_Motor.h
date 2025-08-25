#ifndef __APP_MOTOR_H__
#define __APP_MOTOR_H__

#include "Int_Motor.h"
#include "Com_Define.h"
#include "Com_Debug.h"
#include "Com_Util.h"

/**
 * @brief 初始化 Motor 电机
 * 
 */
void App_Motor_Init(void);

/**
 * @brief 获取 Motor 电机运行方向
 * 
 * @return int8_t 电机运行方向 -1 反方向 1 正方向
 */
int8_t App_Motor_GetDir(void);

/**
 * @brief 获取 Motor 电机 mesure_speed转速
 * 
 * @param dt 时间间隔 单位：秒
 * @note 在任务轮询 dt 时间间隔内调用
 */
void App_Motor_GetSpeed(float dt);

/**
 * @brief 运行 Motor 电机
 * 
 * @param dt 时间间隔 单位：秒
 * @note 在任务轮询 dt 时间间隔内调用
 */
void App_Motor_Run(float dt);

/**
 * @brief 监听 modbus 命令 
 * 
 * @note 使用 modbus , 监听 modbus 命令, 并根据命令执行 打开和关闭电机
 */
void App_Motor_CheckModbus(void);


#endif /* __APP_MOTOR_H__ */
