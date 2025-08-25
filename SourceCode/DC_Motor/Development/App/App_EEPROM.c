#include "App_EEPROM.h"

void App_EEPROM_SaveModbusID(void)
{
    // 标志位 flag : 0-没有保存过，1-已经保存过
    uint8_t flag = 1;

    // 保存标志位
    Int_M24C02_WriteByte(0, flag);

    // 保存 ModbusID
    Int_M24C02_WriteByte(1, g_motor_id);
}

void App_EEPROM_LoadModbusID(void)
{
    // 标志位 flag : 0-没有保存过，1-已经保存过
    uint8_t flag = 0;

    // 读取标志位
    Int_M24C02_ReadByte(0, &flag);
    if (flag == 0)
    {
        // 没有保存过,加载保存默认值
        g_motor_id = 1;
        App_EEPROM_SaveModbusID();
    }
    if (flag == 1)
    {
        // 读取 EEPROM 数据到 g_motor_id
        Int_M24C02_ReadByte(1, &g_motor_id);
    }
}
