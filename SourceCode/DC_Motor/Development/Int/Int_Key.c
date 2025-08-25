#include "Int_Key.h"

Key_Info key_info[KEY_COUNT] = {
    {KEY1_GPIO_Port, KEY1_Pin, KEY_STATE_FREE, KEY_ID_1, KEY_EVENT_KEY1, 0},
    {KEY2_GPIO_Port, KEY2_Pin, KEY_STATE_FREE, KEY_ID_2, KEY_EVENT_KEY2, 0},
    {KEY3_GPIO_Port, KEY3_Pin, KEY_STATE_FREE, KEY_ID_3, KEY_EVENT_KEY3, 0},
    {KEY4_GPIO_Port, KEY4_Pin, KEY_STATE_FREE, KEY_ID_4, KEY_EVENT_KEY4, 0},
};

/**
 * @brief ����ĸ�key������
 * @param key_info ������Ϣ
 * @return Key_Event �����¼�
 * @note ��������ʱ,���ذ����¼�(�ĸ�key����),����δ����ʱ,����KEY_EVENT_NONE
 */
static Key_Event Int_Key_Process(Key_Info *key_info)
{
    // 1 ÿ�ν�����ȡ��ǰʱ��
    uint32_t current_time = xTaskGetTickCount();

    // 2 ������ŵ�״̬
    uint8_t pin_state = HAL_GPIO_ReadPin(key_info->port, key_info->pin);

    // 3 ״̬��
    switch (key_info->key_state)
    {
    case KEY_STATE_FREE:
        // ����ǿ���״̬,�����л�����״̬
        if (pin_state == GPIO_PIN_RESET)
        {
            // �л�����״̬
            key_info->key_state = KEY_STATE_DEBOUNCE;
            // ��¼����ʱ��
            key_info->key_press_time = current_time;
        }
        break;
    case KEY_STATE_DEBOUNCE:
        // ���������״̬,�����л�����״̬ ���� �л�����״̬
        // �л�������״̬
        if (pin_state == GPIO_PIN_SET)
        {
            // �л�������״̬
            key_info->key_state = KEY_STATE_FREE;
        }
        // �л�������״̬
        if ((current_time - key_info->key_press_time) > KEY_DEBOUNCE_TIME)
        {
            // �л�������״̬
            key_info->key_state = KEY_STATE_PRESSED;
        }
        break;
    case KEY_STATE_PRESSED:
        // �л�������״̬ (�����ɿ�)
        if (pin_state == GPIO_PIN_SET)
        {
            // �л�������״̬
            key_info->key_state = KEY_STATE_FREE;
            return key_info->key_event;
        }
    }

    // 4. û�а�������
    return KEY_EVENT_NONE;
}

Key_Event Int_Key_Scan(void)
{
    for (uint8_t i = 0; i < KEY_COUNT; i++)
    {
        // 1. ���key�¼�
        Key_Event key_event = Int_Key_Process(&key_info[i]);
        if (key_event != KEY_EVENT_NONE)
        {
            // ���ذ����¼�
            return key_event;
        }
    }
    // 2. û�а�������
    return KEY_EVENT_NONE;
}
