#include "App_Task.h"

/* ************************************************************************ */
/* ******************************��������*********************************** */
/* ************************************************************************ */

// 1. �������������
#define START_TASK_NAME "start_task"
#define START_TASK_STACK 128
#define START_TASK_PRIORITY 14
TaskHandle_t start_task_handle;
void start_task(void *pvParameters); // ����������

// 2. ��ʾ����
#define DISPLAY_TASK_NAME "display_task"
#define DISPLAY_TASK_STACK 128
#define DISPLAY_TASK_PRIORITY 7
TaskHandle_t display_task_handle;
void display_task(void *pvParameters);
#define DISPLAY_EXEC_CYCLE 10

// 3. ��������
#define KEY_TASK_NAME "key_task"
#define KEY_TASK_STACK 128
#define KEY_TASK_PRIORITY 8
TaskHandle_t key_task_handle;
void key_task(void *pvParameters);
#define KEY_EXEC_CYCLE 10

// 4. EEPROM ����
#define EEPROM_TASK_NAME "eeprom_task"
#define EEPROM_TASK_STACK 128
#define EEPROM_TASK_PRIORITY 14
TaskHandle_t eeprom_task_handle;
void eeprom_task(void *pvParameters);

// 5. �������
#define MOTOR_TASK_NAME "motor_task"
#define MOTOR_TASK_STACK 128
#define MOTOR_TASK_PRIORITY 10
TaskHandle_t motor_task_handle;
void motor_task(void *pvParameters);
#define MOTOR_EXEC_CYCLE 10

// 6. Modbus ����
#define MODBUS_TASK_NAME "modbus_task"
#define MODBUS_TASK_STACK 128
#define MODBUS_TASK_PRIORITY 11
TaskHandle_t modbus_task_handle;
void modbus_task(void *pvParameters);
#define MODBUS_EXEC_CYCLE 10

/* ************************************************************************ */
/* ******************************��������*********************************** */
/* ************************************************************************ */

/**
 * @brief ����FreeRTOS
 */
void App_Task_Start(void)
{
    // 0. �����ʾ
    DEBUG_PRINTLN("���������Ŀ....");

    // 1. ����һ����������,��������𴴽���������
    BaseType_t result = xTaskCreate(
        (TaskFunction_t)start_task,
        (char *)"start_task",
        (configSTACK_DEPTH_TYPE)START_TASK_STACK,
        (void *)NULL,
        (UBaseType_t)START_TASK_PRIORITY,
        (TaskHandle_t *)&start_task_handle);

    if (result == pdPASS)
    {
        DEBUG_PRINTLN("�������񴴽��ɹ�...");
    }
    else
    {
        DEBUG_PRINTLN("�������񴴽�ʧ��...");
    }

    // 2. ����������(�ڲ����Զ�������������)
    vTaskStartScheduler();
}

/* ************************************************************************ */
/* ******************************��������*********************************** */
/* ************************************************************************ */

// ���������������
void start_task(void *pvParameters)
{
    DEBUG_PRINTLN("��������ʼִ��:��ʼ������������....");
    // 1.�����ٽ���
    taskENTER_CRITICAL();

    // 2 . ������ʾ����
    BaseType_t display_result = xTaskCreate(

        (TaskFunction_t)display_task,
        (char *)DISPLAY_TASK_NAME,
        (configSTACK_DEPTH_TYPE)DISPLAY_TASK_STACK,
        (void *)NULL,
        (UBaseType_t)DISPLAY_TASK_PRIORITY,
        (TaskHandle_t *)&display_task_handle);
    if (display_result == pdPASS)
    {
        DEBUG_PRINTLN("��ʾ���񴴽��ɹ�...");
    }
    else
    {
        DEBUG_PRINTLN("��ʾ���񴴽�ʧ��...");
    }

    // 3. ������������
    BaseType_t key_result = xTaskCreate(

        (TaskFunction_t)key_task,
        (char *)KEY_TASK_NAME,
        (configSTACK_DEPTH_TYPE)KEY_TASK_STACK,
        (void *)NULL,
        (UBaseType_t)KEY_TASK_PRIORITY,
        (TaskHandle_t *)&key_task_handle);
    if (key_result == pdPASS)
    {
        DEBUG_PRINTLN("�������񴴽��ɹ�...");
    }
    else
    {
        DEBUG_PRINTLN("�������񴴽�ʧ��...");
    }

    // 4. ���� EEPROM ����
    BaseType_t eeprom_result = xTaskCreate(

        (TaskFunction_t)eeprom_task,
        (char *)EEPROM_TASK_NAME,
        (configSTACK_DEPTH_TYPE)EEPROM_TASK_STACK,
        (void *)NULL,
        (UBaseType_t)EEPROM_TASK_PRIORITY,
        (TaskHandle_t *)&eeprom_task_handle);
    if (eeprom_result == pdPASS)
    {
        DEBUG_PRINTLN("EEPROM���񴴽��ɹ�...");
    }
    else
    {
        DEBUG_PRINTLN("EEPROM���񴴽�ʧ��...");
    }

    // 5. �����������
    BaseType_t motor_result = xTaskCreate(

        (TaskFunction_t)motor_task,
        (char *)MOTOR_TASK_NAME,
        (configSTACK_DEPTH_TYPE)MOTOR_TASK_STACK,
        (void *)NULL,
        (UBaseType_t)MOTOR_TASK_PRIORITY,
        (TaskHandle_t *)&motor_task_handle);
    if (motor_result == pdPASS)
    {
        DEBUG_PRINTLN("������񴴽��ɹ�...");
    }
    else
    {
        DEBUG_PRINTLN("������񴴽�ʧ��...");
    }

    // 6. ���� Modbus ����
    BaseType_t modbus_result = xTaskCreate(

        (TaskFunction_t)modbus_task,
        (char *)MODBUS_TASK_NAME,
        (configSTACK_DEPTH_TYPE)MODBUS_TASK_STACK,
        (void *)NULL,
        (UBaseType_t)MODBUS_TASK_PRIORITY,
        (TaskHandle_t *)&modbus_task_handle);
    if (modbus_result == pdPASS)
    {
        DEBUG_PRINTLN("Modbus���񴴽��ɹ�...");
    }
    else
    {
        DEBUG_PRINTLN("Modbus���񴴽�ʧ��...");
    }

    // �˳��ٽ���
    taskEXIT_CRITICAL();

    // 6. ɾ����������
    vTaskDelete(NULL);
}

/* ************************************************************************ */
/* ******************************������*********************************** */
/* ************************************************************************ */

// ��ʾ������
void display_task(void *pvParameters)
{
    DEBUG_PRINTLN("��ʾ����: ��ʼ����");
    App_Display_Init();
    uint32_t preTime = xTaskGetTickCount();
    while (1)
    {
        // OLED��ʾ
        App_Display_Show();
        xTaskDelayUntil(&preTime, DISPLAY_EXEC_CYCLE);
    }
}

// ����������
void key_task(void *pvParameters)
{
    DEBUG_PRINTLN("��������: ��ʼ����");
    uint32_t preTime = xTaskGetTickCount();
    while (1)
    {
        // �������¼�
        App_Key_Handle();
        xTaskDelayUntil(&preTime, KEY_EXEC_CYCLE);
    }
}

// EEPROM ������
void eeprom_task(void *pvParameters)
{
    DEBUG_PRINTLN("EEPROM����: ��ʼ����");
    // ��ʼ������ ModbusID
    App_EEPROM_LoadModbusID();
    while (1)
    {
        // �ȴ�֪ͨ
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        // ���� ModbusID
        App_EEPROM_SaveModbusID();
    }
}

// ���������
void motor_task(void *pvParameters)
{
    DEBUG_PRINTLN("�������: ��ʼ����");
    App_Motor_Init();
    uint32_t preTime = xTaskGetTickCount();
    float dt = MOTOR_EXEC_CYCLE / 1000.0;
    while (1)
    {
        // ���е��
        App_Motor_Run(dt);
        // ��� Modbus ͨ��
        App_Motor_CheckModbus();
        // ���µ������
        App_Motor_GetDir();

        vTaskDelayUntil(&preTime, MOTOR_EXEC_CYCLE);
    }
}

// Modbus ������
void modbus_task(void *pvParameters)
{
    DEBUG_PRINTLN("Modbus����: ��ʼ����");
    App_Modbus_Init();
    uint32_t preTime = xTaskGetTickCount();
    while (1)
    {
        // ���� Modbus ͨ��
        App_Modbus_Handle();
        vTaskDelayUntil(&preTime, MODBUS_EXEC_CYCLE);
    }
}

