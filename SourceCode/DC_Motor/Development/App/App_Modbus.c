#include "App_Modbus.h"

void App_Modbus_Init(void)
{
    // ��ʼ��Modbus,�˴��Ĳ����ʲ���Ч=> ֱ��ʹ�õ�HAL��  ���һ����������żУ��λ
    eMBInit(MB_RTU, g_motor_id, 0, 115200, MB_PAR_NONE);
    // ����ModbusЭ��ջ
    eMBEnable();
}


void App_Modbus_Handle(void)
{
    // ��ѵ���ý������ݵķ���
    eMBPoll();
}