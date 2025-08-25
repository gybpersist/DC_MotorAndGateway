#ifndef __APP_TASK_H__
#define __APP_TASK_H__

#include "FreeRTOS.h"
#include "task.h"
#include "Com_Debug.h"
#include "App_Display.h"
#include "App_Key.h"
#include "App_EEPROM.h"
#include "App_Motor.h"
#include "App_Modbus.h"

/**
 * @brief ����FreeRTOS
 */
void App_Task_Start(void);

/**
 * @brief ���������������
 * 
 * @param pvParameters 
 */

void start_task(void *pvParameters);

#endif /* __APP_TASK_H__ */
