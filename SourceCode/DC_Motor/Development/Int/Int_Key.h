#ifndef __INT_KEY_H__
#define __INT_KEY_H__

#include "gpio.h"
#include "FreeRTOS.h"
#include "task.h"

#define KEY_DEBOUNCE_TIME 10 // ����ʱ�� 10ms

// ��ǰkey��״̬
typedef enum
{
    KEY_STATE_FREE = 0,  // ��������
    KEY_STATE_DEBOUNCE,  // ����
    KEY_STATE_PRESSED,   // ��������
} Key_State;

// ��ǰkey��ID
typedef enum
{
    KEY_ID_1 = 0, // ����1
    KEY_ID_2,     // ����2
    KEY_ID_3,     // ����3
    KEY_ID_4,     // ����4
    KEY_COUNT, // ��������
} Key_ID;

// ��ǰkey���µ��¼� (�ĸ�key����)
typedef enum
{
    KEY_EVENT_NONE = -1, // ���¼�
    KEY_EVENT_KEY1,      // ����1����
    KEY_EVENT_KEY2,      // ����2����
    KEY_EVENT_KEY3,      // ����3����
    KEY_EVENT_KEY4,      // ����4����
} Key_Event;

// ��ǰkey����Ϣ
typedef struct 
{
    GPIO_TypeDef *port;     // ��ǰkey��port
    uint16_t pin;           // ��ǰkey��pin
    Key_State key_state;    // ��ǰkey��״̬
    Key_ID key_id;          // ��ǰkey��ID
    Key_Event key_event;    // ��ǰkey���µ��¼� (�ĸ�key����)
    uint32_t key_press_time;// ��ǰkey���µ�ʱ��
} Key_Info;

/**
 * @brief ����ɨ��
 * 
 * @return Key_Event �����¼�
 * @note ��������ʱ,���ذ����¼�(�ĸ�key����),����δ����ʱ,����KEY_EVENT_NONE
 */
Key_Event Int_Key_Scan(void);

#endif /* __INT_KEY_H__ */
