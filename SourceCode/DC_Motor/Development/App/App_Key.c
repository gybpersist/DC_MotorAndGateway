#include "App_Key.h"

void App_Key_Handle(void)
{
    Key_Event key_event = Int_Key_Scan();

    // 1 �������¼�
    switch (key_event)
    {
    case KEY_EVENT_KEY1:
        DEBUG_PRINTLN("KEY1 ������...");
        // �жϵ�ǰģʽ
        // ���ģʽ
        if (gs_key_mode == KEY_MODE_MOTOR)
        {
            // ���ģʽ��,KEY1�����ٶ�
            g_desired_speed += 10;
            g_desired_speed = LIMIT(g_desired_speed, -280, 280);
            REG_HOLD_BUF[2] = g_desired_speed + 500;
            DEBUG_PRINTLN("��ǰ�ٶ�: %d", g_desired_speed);
        }
        // IDģʽ
        else if (gs_key_mode == KEY_MODE_ID)
        {
            // IDģʽ��,KEY1����ID
            g_motor_id += 1;
            g_motor_id = LIMIT(g_motor_id, 1, 10);
            // ����EEPROM����֪ͨ
            xTaskNotifyGive(eeprom_task_handle);
            DEBUG_PRINTLN("��ǰID: %d", g_motor_id);
        }
        break;
    case KEY_EVENT_KEY2:
        DEBUG_PRINTLN("KEY2 ������...");
        // �жϵ�ǰģʽ
        // ���ģʽ
        if (gs_key_mode == KEY_MODE_MOTOR)
        {
            // ���ģʽ��,KEY2�����ٶ�
            g_desired_speed -= 10;
            g_desired_speed = LIMIT(g_desired_speed, -280, 280);
            REG_HOLD_BUF[2] = g_desired_speed + 500;
            DEBUG_PRINTLN("��ǰ�ٶ�: %d", g_desired_speed);
        }
        // IDģʽ
        else if (gs_key_mode == KEY_MODE_ID)
        {
            // IDģʽ��,KEY2����ID
            g_motor_id -= 1;
            g_motor_id = LIMIT(g_motor_id, 1, 10);
            // ����EEPROM����֪ͨ
            xTaskNotifyGive(eeprom_task_handle);
            DEBUG_PRINTLN("��ǰID: %d", g_motor_id);
        }
        break;
    case KEY_EVENT_KEY3:
        DEBUG_PRINTLN("KEY3 ������...");
        // �жϵ�ǰģʽ
        // ���ģʽ
        if (gs_key_mode == KEY_MODE_MOTOR)
        {
            // ���ģʽ��,KEY3����ٶ�
            g_desired_speed = 0;
            REG_HOLD_BUF[2] = g_desired_speed + 500;
            DEBUG_PRINTLN("��ǰ�ٶ�: %d", g_desired_speed);
        }
        // IDģʽ
        else if (gs_key_mode == KEY_MODE_ID)
        {
            // IDģʽ��,KEY3���ID (Ĭ��Ϊ1)
            g_motor_id = 1;
            // ����EEPROM����֪ͨ
            xTaskNotifyGive(eeprom_task_handle);
            DEBUG_PRINTLN("��ǰID: %d", g_motor_id);
        }
        break;
    case KEY_EVENT_KEY4:
        DEBUG_PRINTLN("KEY4 ������...");
        // �л�����ģʽ
        gs_key_mode = (gs_key_mode == KEY_MODE_MOTOR) ? KEY_MODE_ID : KEY_MODE_MOTOR;
        // �л�����ģʽ�󣬴�ӡ��ǰģʽ
        DEBUG_PRINTLN("��ǰ����ģʽ: %s", (gs_key_mode == KEY_MODE_MOTOR) ? "���ģʽ" : "IDģʽ");
        break;
    }

    // �����ٶȺ�ID��Χ
    // g_motor_speed = LIMIT(g_motor_speed, -280, 280);
    // g_motor_id = LIMIT(g_motor_id, 1, 255);
    // DEBUG_PRINTLN("��ǰ�ٶ�: %d, ��ǰID: %d", g_motor_speed, g_motor_id);
}
