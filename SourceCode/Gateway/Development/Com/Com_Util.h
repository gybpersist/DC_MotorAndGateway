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

#endif /* __COM_UTIL_H__ */
