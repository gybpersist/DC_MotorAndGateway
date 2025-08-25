#include "App_EEPROM.h"

void App_EEPROM_SaveModbusID(void)
{
    // ��־λ flag : 0-û�б������1-�Ѿ������
    uint8_t flag = 1;

    // �����־λ
    Int_M24C02_WriteByte(0, flag);

    // ���� ModbusID
    Int_M24C02_WriteByte(1, g_motor_id);
}

void App_EEPROM_LoadModbusID(void)
{
    // ��־λ flag : 0-û�б������1-�Ѿ������
    uint8_t flag = 0;

    // ��ȡ��־λ
    Int_M24C02_ReadByte(0, &flag);
    if (flag == 0)
    {
        // û�б����,���ر���Ĭ��ֵ
        g_motor_id = 1;
        App_EEPROM_SaveModbusID();
    }
    if (flag == 1)
    {
        // ��ȡ EEPROM ���ݵ� g_motor_id
        Int_M24C02_ReadByte(1, &g_motor_id);
    }
}
