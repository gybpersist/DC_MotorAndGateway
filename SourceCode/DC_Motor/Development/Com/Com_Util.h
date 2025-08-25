#ifndef __COM_UTIL_H__
#define __COM_UTIL_H__

#include <stdio.h>
#include "main.h"
#include "time.h"

/**
 * @brief 延时多少 us
 * 
 * @param us 延时时间
 */
void Com_Delay_us(uint16_t us);

/**
 * @brief 延时多少 ms
 * 
 * @param ms 延时时间
 */
void Com_Delay_ms(uint16_t ms);

/**
 * @brief 将 UTC 时间转换为本地时间(北京时间)
 * 
 * @param utc_time 要转换的 UTC 时间
 * @param local_time 转换好的本地时间(北京时间)
 * @note 输入的 utc_time 格式为 "YYYY-MM-DD hh:mm:ss"
 * @note 输出的 local_time 格式为 "YYYY-MM-DD hh:mm:ss"
 */
void Com_UTC2LocalTime(uint8_t *utc_time, uint8_t *local_time);

// 定义 PID 结构体
typedef struct
{
    float Kp; // 比例系数
    float Ki; // 积分系数
    float Kd; // 微分系数
    
    float dt; // 采样时间

    float desired;     // 期望值
    float measure;     // 测量值

    float integral;    // 积分项
    float last_error;  // 上一次的误差
    
    float result;      // PID 输出结果
}PID_Info;

/**
 * @brief PID 算法
 * 
 * @param pid PID 结构体指针
 */
void Com_Util_PID(PID_Info *pid);

#endif /* __COM_UTIL_H__ */
