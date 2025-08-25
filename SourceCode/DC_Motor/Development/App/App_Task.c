#include "App_Task.h"

/* ************************************************************************ */
/* ******************************任务配置*********************************** */
/* ************************************************************************ */

// 1. 启动任务的配置
#define START_TASK_NAME "start_task"
#define START_TASK_STACK 128
#define START_TASK_PRIORITY 14
TaskHandle_t start_task_handle;
void start_task(void *pvParameters); // 启动任务函数

// 2. 显示任务
#define DISPLAY_TASK_NAME "display_task"
#define DISPLAY_TASK_STACK 128
#define DISPLAY_TASK_PRIORITY 7
TaskHandle_t display_task_handle;
void display_task(void *pvParameters);
#define DISPLAY_EXEC_CYCLE 10

// 3. 按键任务
#define KEY_TASK_NAME "key_task"
#define KEY_TASK_STACK 128
#define KEY_TASK_PRIORITY 8
TaskHandle_t key_task_handle;
void key_task(void *pvParameters);
#define KEY_EXEC_CYCLE 10

// 4. EEPROM 任务
#define EEPROM_TASK_NAME "eeprom_task"
#define EEPROM_TASK_STACK 128
#define EEPROM_TASK_PRIORITY 14
TaskHandle_t eeprom_task_handle;
void eeprom_task(void *pvParameters);

// 5. 电机任务
#define MOTOR_TASK_NAME "motor_task"
#define MOTOR_TASK_STACK 128
#define MOTOR_TASK_PRIORITY 10
TaskHandle_t motor_task_handle;
void motor_task(void *pvParameters);
#define MOTOR_EXEC_CYCLE 10

// 6. Modbus 任务
#define MODBUS_TASK_NAME "modbus_task"
#define MODBUS_TASK_STACK 128
#define MODBUS_TASK_PRIORITY 11
TaskHandle_t modbus_task_handle;
void modbus_task(void *pvParameters);
#define MODBUS_EXEC_CYCLE 10

/* ************************************************************************ */
/* ******************************启动函数*********************************** */
/* ************************************************************************ */

/**
 * @brief 启动FreeRTOS
 */
void App_Task_Start(void)
{
    // 0. 输出提示
    DEBUG_PRINTLN("电机控制项目....");

    // 1. 创建一个启动任务,这个任务负责创建其他任务
    BaseType_t result = xTaskCreate(
        (TaskFunction_t)start_task,
        (char *)"start_task",
        (configSTACK_DEPTH_TYPE)START_TASK_STACK,
        (void *)NULL,
        (UBaseType_t)START_TASK_PRIORITY,
        (TaskHandle_t *)&start_task_handle);

    if (result == pdPASS)
    {
        DEBUG_PRINTLN("启动任务创建成功...");
    }
    else
    {
        DEBUG_PRINTLN("启动任务创建失败...");
    }

    // 2. 启动调度器(内部会自动创建空闲任务)
    vTaskStartScheduler();
}

/* ************************************************************************ */
/* ******************************创建任务*********************************** */
/* ************************************************************************ */

// 启动任务的任务函数
void start_task(void *pvParameters)
{
    DEBUG_PRINTLN("启动任务开始执行:开始创建其他任务....");
    // 1.进入临界区
    taskENTER_CRITICAL();

    // 2 . 创建显示任务
    BaseType_t display_result = xTaskCreate(

        (TaskFunction_t)display_task,
        (char *)DISPLAY_TASK_NAME,
        (configSTACK_DEPTH_TYPE)DISPLAY_TASK_STACK,
        (void *)NULL,
        (UBaseType_t)DISPLAY_TASK_PRIORITY,
        (TaskHandle_t *)&display_task_handle);
    if (display_result == pdPASS)
    {
        DEBUG_PRINTLN("显示任务创建成功...");
    }
    else
    {
        DEBUG_PRINTLN("显示任务创建失败...");
    }

    // 3. 创建按键任务
    BaseType_t key_result = xTaskCreate(

        (TaskFunction_t)key_task,
        (char *)KEY_TASK_NAME,
        (configSTACK_DEPTH_TYPE)KEY_TASK_STACK,
        (void *)NULL,
        (UBaseType_t)KEY_TASK_PRIORITY,
        (TaskHandle_t *)&key_task_handle);
    if (key_result == pdPASS)
    {
        DEBUG_PRINTLN("按键任务创建成功...");
    }
    else
    {
        DEBUG_PRINTLN("按键任务创建失败...");
    }

    // 4. 创建 EEPROM 任务
    BaseType_t eeprom_result = xTaskCreate(

        (TaskFunction_t)eeprom_task,
        (char *)EEPROM_TASK_NAME,
        (configSTACK_DEPTH_TYPE)EEPROM_TASK_STACK,
        (void *)NULL,
        (UBaseType_t)EEPROM_TASK_PRIORITY,
        (TaskHandle_t *)&eeprom_task_handle);
    if (eeprom_result == pdPASS)
    {
        DEBUG_PRINTLN("EEPROM任务创建成功...");
    }
    else
    {
        DEBUG_PRINTLN("EEPROM任务创建失败...");
    }

    // 5. 创建电机任务
    BaseType_t motor_result = xTaskCreate(

        (TaskFunction_t)motor_task,
        (char *)MOTOR_TASK_NAME,
        (configSTACK_DEPTH_TYPE)MOTOR_TASK_STACK,
        (void *)NULL,
        (UBaseType_t)MOTOR_TASK_PRIORITY,
        (TaskHandle_t *)&motor_task_handle);
    if (motor_result == pdPASS)
    {
        DEBUG_PRINTLN("电机任务创建成功...");
    }
    else
    {
        DEBUG_PRINTLN("电机任务创建失败...");
    }

    // 6. 创建 Modbus 任务
    BaseType_t modbus_result = xTaskCreate(

        (TaskFunction_t)modbus_task,
        (char *)MODBUS_TASK_NAME,
        (configSTACK_DEPTH_TYPE)MODBUS_TASK_STACK,
        (void *)NULL,
        (UBaseType_t)MODBUS_TASK_PRIORITY,
        (TaskHandle_t *)&modbus_task_handle);
    if (modbus_result == pdPASS)
    {
        DEBUG_PRINTLN("Modbus任务创建成功...");
    }
    else
    {
        DEBUG_PRINTLN("Modbus任务创建失败...");
    }

    // 退出临界区
    taskEXIT_CRITICAL();

    // 6. 删除启动任务
    vTaskDelete(NULL);
}

/* ************************************************************************ */
/* ******************************任务函数*********************************** */
/* ************************************************************************ */

// 显示任务函数
void display_task(void *pvParameters)
{
    DEBUG_PRINTLN("显示任务: 开始调度");
    App_Display_Init();
    uint32_t preTime = xTaskGetTickCount();
    while (1)
    {
        // OLED显示
        App_Display_Show();
        xTaskDelayUntil(&preTime, DISPLAY_EXEC_CYCLE);
    }
}

// 按键任务函数
void key_task(void *pvParameters)
{
    DEBUG_PRINTLN("按键任务: 开始调度");
    uint32_t preTime = xTaskGetTickCount();
    while (1)
    {
        // 处理按键事件
        App_Key_Handle();
        xTaskDelayUntil(&preTime, KEY_EXEC_CYCLE);
    }
}

// EEPROM 任务函数
void eeprom_task(void *pvParameters)
{
    DEBUG_PRINTLN("EEPROM任务: 开始调度");
    // 初始化加载 ModbusID
    App_EEPROM_LoadModbusID();
    while (1)
    {
        // 等待通知
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        // 保存 ModbusID
        App_EEPROM_SaveModbusID();
    }
}

// 电机任务函数
void motor_task(void *pvParameters)
{
    DEBUG_PRINTLN("电机任务: 开始调度");
    App_Motor_Init();
    uint32_t preTime = xTaskGetTickCount();
    float dt = MOTOR_EXEC_CYCLE / 1000.0;
    while (1)
    {
        // 运行电机
        App_Motor_Run(dt);
        // 检查 Modbus 通信
        App_Motor_CheckModbus();
        // 更新电机方向
        App_Motor_GetDir();

        vTaskDelayUntil(&preTime, MOTOR_EXEC_CYCLE);
    }
}

// Modbus 任务函数
void modbus_task(void *pvParameters)
{
    DEBUG_PRINTLN("Modbus任务: 开始调度");
    App_Modbus_Init();
    uint32_t preTime = xTaskGetTickCount();
    while (1)
    {
        // 处理 Modbus 通信
        App_Modbus_Handle();
        vTaskDelayUntil(&preTime, MODBUS_EXEC_CYCLE);
    }
}

