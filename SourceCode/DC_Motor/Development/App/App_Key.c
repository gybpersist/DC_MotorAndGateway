#include "App_Key.h"

void App_Key_Handle(void)
{
    Key_Event key_event = Int_Key_Scan();

    // 1 处理按键事件
    switch (key_event)
    {
    case KEY_EVENT_KEY1:
        DEBUG_PRINTLN("KEY1 被按下...");
        // 判断当前模式
        // 电机模式
        if (gs_key_mode == KEY_MODE_MOTOR)
        {
            // 电机模式下,KEY1增加速度
            g_desired_speed += 10;
            g_desired_speed = LIMIT(g_desired_speed, -280, 280);
            REG_HOLD_BUF[2] = g_desired_speed + 500;
            DEBUG_PRINTLN("当前速度: %d", g_desired_speed);
        }
        // ID模式
        else if (gs_key_mode == KEY_MODE_ID)
        {
            // ID模式下,KEY1增加ID
            g_motor_id += 1;
            g_motor_id = LIMIT(g_motor_id, 1, 10);
            // 发送EEPROM任务通知
            xTaskNotifyGive(eeprom_task_handle);
            DEBUG_PRINTLN("当前ID: %d", g_motor_id);
        }
        break;
    case KEY_EVENT_KEY2:
        DEBUG_PRINTLN("KEY2 被按下...");
        // 判断当前模式
        // 电机模式
        if (gs_key_mode == KEY_MODE_MOTOR)
        {
            // 电机模式下,KEY2减少速度
            g_desired_speed -= 10;
            g_desired_speed = LIMIT(g_desired_speed, -280, 280);
            REG_HOLD_BUF[2] = g_desired_speed + 500;
            DEBUG_PRINTLN("当前速度: %d", g_desired_speed);
        }
        // ID模式
        else if (gs_key_mode == KEY_MODE_ID)
        {
            // ID模式下,KEY2减少ID
            g_motor_id -= 1;
            g_motor_id = LIMIT(g_motor_id, 1, 10);
            // 发送EEPROM任务通知
            xTaskNotifyGive(eeprom_task_handle);
            DEBUG_PRINTLN("当前ID: %d", g_motor_id);
        }
        break;
    case KEY_EVENT_KEY3:
        DEBUG_PRINTLN("KEY3 被按下...");
        // 判断当前模式
        // 电机模式
        if (gs_key_mode == KEY_MODE_MOTOR)
        {
            // 电机模式下,KEY3清空速度
            g_desired_speed = 0;
            REG_HOLD_BUF[2] = g_desired_speed + 500;
            DEBUG_PRINTLN("当前速度: %d", g_desired_speed);
        }
        // ID模式
        else if (gs_key_mode == KEY_MODE_ID)
        {
            // ID模式下,KEY3清空ID (默认为1)
            g_motor_id = 1;
            // 发送EEPROM任务通知
            xTaskNotifyGive(eeprom_task_handle);
            DEBUG_PRINTLN("当前ID: %d", g_motor_id);
        }
        break;
    case KEY_EVENT_KEY4:
        DEBUG_PRINTLN("KEY4 被按下...");
        // 切换按键模式
        gs_key_mode = (gs_key_mode == KEY_MODE_MOTOR) ? KEY_MODE_ID : KEY_MODE_MOTOR;
        // 切换按键模式后，打印当前模式
        DEBUG_PRINTLN("当前按键模式: %s", (gs_key_mode == KEY_MODE_MOTOR) ? "电机模式" : "ID模式");
        break;
    }

    // 限制速度和ID范围
    // g_motor_speed = LIMIT(g_motor_speed, -280, 280);
    // g_motor_id = LIMIT(g_motor_id, 1, 255);
    // DEBUG_PRINTLN("当前速度: %d, 当前ID: %d", g_motor_speed, g_motor_id);
}
