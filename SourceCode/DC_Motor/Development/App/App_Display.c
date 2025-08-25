#include "App_Display.h"

/**
 * @brief 初始化
 */
void App_Display_Init(void)
{
    // 1. 初始化LED
    Inf_OLED_Init();

    // 2. 第一行显示汉字
    for (uint16_t i = 3; i < 7; i++)
    {
        Inf_OLED_ShowChinese(16 * 0 + 16 * (i - 3), 0, i, 16, 1);
    }
}

void App_Display_Show(void)
{
    // 2. 第二行显示 设置的速度:desired: 00020
    if (gs_key_mode == KEY_MODE_MOTOR)
    {
        Inf_OLED_ShowString(0, 16, "*", 16, 1);
    }
    else
    {
        Inf_OLED_ShowString(0, 16, " ", 16, 1);
    }

    Inf_OLED_ShowString(8, 16, "desired:", 16, 1);
    if (g_desired_speed >= 0)
    {
        Inf_OLED_ShowString(72, 16, " ", 16, 1);
        Inf_OLED_ShowNum(80, 16, g_desired_speed, 5, 16, 1);
    }
    else
    {
        Inf_OLED_ShowString(72, 16, "-", 16, 1);
        Inf_OLED_ShowNum(80, 16, -g_desired_speed, 5, 16, 1);

    }

    // 3. 第三行显示 测量的速度:mesure: 00019
    if (gs_key_mode == KEY_MODE_MOTOR)
    {
        Inf_OLED_ShowString(0, 32, "*", 16, 1);
    }
    else
    {
        Inf_OLED_ShowString(0, 32, " ", 16, 1);
    }
    // Inf_OLED_ShowString(8, 32, "mesure:", 16, 1);                //优化
    Inf_OLED_ShowString(8, 32, "mesure :", 16, 1);
    if (g_mesure_speed >= 0)
    {
        // Inf_OLED_ShowString(64, 32, " ", 16, 1);                 //优化
        // Inf_OLED_ShowNum(72, 32, g_mesure_speed, 5, 16, 1);      //优化
        Inf_OLED_ShowString(72, 32, " ", 16, 1);
        Inf_OLED_ShowNum(80, 32, g_mesure_speed, 5, 16, 1);
    }
    else
    {
        // Inf_OLED_ShowString(64, 32, "-", 16, 1);                 //优化
        // Inf_OLED_ShowNum(72, 32, -g_mesure_speed, 5, 16, 1);     //优化

        Inf_OLED_ShowString(72, 32, "-", 16, 1);
        Inf_OLED_ShowNum(80, 32, -g_mesure_speed, 5, 16, 1);
    }
    // 4. 第四行显示 modbus的id: modbus_id:001
    if (gs_key_mode == KEY_MODE_ID)
    {
        Inf_OLED_ShowString(0, 48, "*", 16, 1);
    }
    else
    {
        Inf_OLED_ShowString(0, 48, " ", 16, 1);
    }
    Inf_OLED_ShowString(8, 48, "modbus_id:", 16, 1);
    // Inf_OLED_ShowNum(88, 48, g_motor_id, 3, 16, 1);            //优化
    Inf_OLED_ShowNum(96, 48, g_motor_id, 3, 16, 1);

    // 3. 刷新屏幕
    Inf_OLED_Refresh();
}
