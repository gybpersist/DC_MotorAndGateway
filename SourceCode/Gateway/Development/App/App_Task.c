#include "App_Task.h"

// 1. �������������
#define START_TASK_NAME "start_task"
#define START_TASK_STACK 128
#define START_TASK_PRIORITY 14
TaskHandle_t start_task_handle;
void start_task(void *pvParameters); // ����������

// 2. W5500 ���������
#define W5500_TASK_NAME "w5500_task"
#define W5500_TASK_STACK 1024
#define W5500_TASK_PRIORITY 10
TaskHandle_t w5500_task_handle;
void w5500_task(void *pvParameters); // W5500 ������
#define W5500_DELAY_TIME 50

// 3. Modbus ���������
#define MODBUS_TASK_NAME "modbus_task"
#define MODBUS_TASK_STACK 1024
#define MODBUS_TASK_PRIORITY 10
TaskHandle_t modbus_task_handle;
void modbus_task(void *pvParameters); // Modbus ������

/* ������������� */
/* code */

/**
 * @brief ����FreeRTOS
 */
void App_Task_Start(void)
{
    // 0. �����ʾ
    DEBUG_PRINTLN("������Ŀ����....");

    // 1. ����һ������������������𴴽���������
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

// ���������ִ�к���
void start_task(void *pvParameters)
{
    DEBUG_PRINTLN("��������ʼִ��: ��ʼ������������....");
    // 1.�����ٽ���
    taskENTER_CRITICAL();

    /* ������������ */
    /* code */

    // 2. ���� W5500 ����
    BaseType_t w5500_result = xTaskCreate(

        (TaskFunction_t)w5500_task,
        (char *)W5500_TASK_NAME,
        (configSTACK_DEPTH_TYPE)W5500_TASK_STACK,
        (void *)NULL,
        (UBaseType_t)W5500_TASK_PRIORITY,
        (TaskHandle_t *)&w5500_task_handle);
    if (w5500_result == pdPASS)

    {
        DEBUG_PRINTLN("W5500 ���񴴽��ɹ�...");
    }
    else
    {
        DEBUG_PRINTLN("W5500 ���񴴽�ʧ��...");
    }

    // 3. ���� Modbus ����
    BaseType_t modbus_result = xTaskCreate(
        (TaskFunction_t)modbus_task,
        (char *)MODBUS_TASK_NAME,
        (configSTACK_DEPTH_TYPE)MODBUS_TASK_STACK,
        (void *)NULL,
        (UBaseType_t)MODBUS_TASK_PRIORITY,
        (TaskHandle_t *)&modbus_task_handle);
    if (modbus_result == pdPASS)
    {
        DEBUG_PRINTLN("Modbus ���񴴽��ɹ�...");
    }
    else
    {
        DEBUG_PRINTLN("Modbus ���񴴽�ʧ��...");
    }

    // �˳��ٽ���
    taskEXIT_CRITICAL();

    // 4. ɾ����������
    vTaskDelete(NULL);
}

// W5500 �����ִ�к���
void w5500_task(void *pvParameters)
{
    DEBUG_PRINTLN("W5500 ����ʼִ��...");
    App_W5500_Init();
    // ��ȡ��ǰʱ��
    uint32_t current_time = xTaskGetTickCount();
    while (1)
    {
        App_MQTT_Receive();
        xTaskDelayUntil(&current_time, W5500_DELAY_TIME);
    }
}

// Modbus �����ִ�к���
uint8_t modbus_rx_buffer[256];
uint16_t modbus_rx_len;
void modbus_task(void *pvParameters)
{
    DEBUG_PRINTLN("Modbus ����ʼִ��...");
    // ʹ�ô��ڽ��ղ���������
    HAL_UARTEx_ReceiveToIdle_IT(&huart2, modbus_rx_buffer, 256);
    while (1)
    {
        // �ȴ�����֪ͨ
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        // ���� Modbus ����
        Int_Modbus_ResponseParse(modbus_rx_buffer,modbus_rx_len);

        // ��ӡ���յ�������
        for (int i = 0; i < modbus_rx_len; i++)
        {
            printf("0x%02x\t", modbus_rx_buffer[i]);
        }
        printf("\n");
    }
}

// UART �����¼��ص����� !ÿ�ε���ǰ��Ҫ����UART�����ж�
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
    debug_printfln("\n���յ�����....");

    modbus_rx_len = Size;

    // ��������֪ͨ
    vTaskNotifyGiveFromISR(modbus_task_handle, NULL);

    // ʹ�ô��ڽ��ղ���������
    HAL_UARTEx_ReceiveToIdle_IT(&huart2, modbus_rx_buffer, 256);
}
