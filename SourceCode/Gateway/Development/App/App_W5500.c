#include "App_W5500.h"

void App_W5500_Init(void)
{
    // 1. ��ʼ�� W5500
    Int_W5500_Init();
}

void App_MQTT_Receive(void)
{
    // ���ն�����Ϣ
    Int_MQTT_Receive();
}
