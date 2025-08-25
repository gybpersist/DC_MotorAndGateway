#include "Int_Modbus.h"

void Int_Modbus_Send(uint8_t *data, uint16_t len)
{
    // ��ӡ���͵�����
    printf("\n");
    debug_printfln("��������....");
    for (uint16_t i = 0; i < len; i++)
    {
        printf("0x%02X ", data[i]);
    }

    HAL_UART_Transmit(&huart2, data, len, 1000);
    HAL_Delay(1000);
}

void Int_Modbus_WriteCoil(uint8_t id, uint16_t addr, uint8_t value)
{
    uint8_t cmd[8];

    // д����Ȧ ������:0x05
    // ���ݸ�ʽ:id ������ ��ַ�� ��ַ�� ���ݸ� ���ݵ� У��� У���

    cmd[0] = id; // modbus_id

    cmd[1] = 0x05; // ������

    cmd[2] = (addr >> 8) & 0xFF; // ��ַ��
    cmd[3] = (addr >> 0) & 0xFF; // ��ַ��

    cmd[4] = ((value == 0) ? 0x00 : 0xFF); // ���ݸ�
    cmd[5] = 0x00;                       // ���ݵ�

    uint16_t crcvalue = usMBCRC16(cmd, 6);
    cmd[6] = (crcvalue >> 0) & 0xFF; // У���
    cmd[7] = (crcvalue >> 8) & 0xFF; // У���

    Int_Modbus_Send(cmd, 8); // ��������
}

void Int_Modbus_ReadCoil(uint8_t id, uint16_t addr)
{
    uint8_t cmd[8];

    // ��ȡ��Ȧ ������:0x01
    // ���ݸ�ʽ:id ������ ��ַ�� ��ַ�� ���ݸ� ���ݵ� У��� У���

    cmd[0] = id; // modbus_id

    cmd[1] = 0x01; // ������

    cmd[2] = (addr >> 8) & 0xFF; // ��ַ��
    cmd[3] = (addr >> 0) & 0xFF; // ��ַ��

    cmd[4] = 0x00; // ���ݸ�
    cmd[5] = 0x01; // ���ݵ�

    uint16_t crcvalue = usMBCRC16(cmd, 6);
    cmd[6] = (crcvalue >> 0) & 0xFF; // У���
    cmd[7] = (crcvalue >> 8) & 0xFF; // У���

    Int_Modbus_Send(cmd, 8); // ��������
}

void Int_Modbus_WriteHOLD(uint8_t id, uint16_t addr, uint16_t value)
{
    uint8_t cmd[8];

    // д�뱣�ּĴ��� ������:0x06
    // ���ݸ�ʽ:id ������ ��ַ�� ��ַ�� ���ݸ� ���ݵ� У��� У���

    cmd[0] = id; // modbus_id

    cmd[1] = 0x06; // ������

    cmd[2] = (addr >> 8) & 0xFF; // ��ַ��
    cmd[3] = (addr >> 0) & 0xFF; // ��ַ��

    cmd[4] = (value >> 8) & 0xFF; // ���ݸ�
    cmd[5] = (value >> 0) & 0xFF; // ���ݵ�

    uint16_t crcvalue = usMBCRC16(cmd, 6);
    cmd[6] = (crcvalue >> 0) & 0xFF; // У���
    cmd[7] = (crcvalue >> 8) & 0xFF; // У���

    Int_Modbus_Send(cmd, 8); // ��������
}

void Int_Modbus_ReadINPUT(uint8_t id,uint16_t addr)
{
    uint8_t cmd[8];

    // ��ȡ����Ĵ��� ������:0x04
    // ���ݸ�ʽ:id ������ ��ַ�� ��ַ�� ���ݸ� ���ݵ� У��� У���

    cmd[0] = id; // modbus_id

    cmd[1] = 0x04; // ������

    cmd[2] = (addr >> 8) & 0xFF; // ��ַ��
    cmd[3] = (addr >> 0) & 0xFF; // ��ַ��

    cmd[4] = 0x00; // ���ݸ�
    cmd[5] = 0x01; // ���ݵ�

    uint16_t crcvalue = usMBCRC16(cmd, 6);
    cmd[6] = (crcvalue >> 0) & 0xFF; // У���
    cmd[7] = (crcvalue >> 8) & 0xFF; // У���

    Int_Modbus_Send(cmd, 8); // ��������
}

void Int_Modbus_ReadDISC(uint8_t id,uint16_t addr)
{
    uint8_t cmd[8];

    // ��ȡ��ɢ�� ������:0x02
    // ���ݸ�ʽ:id ������ ��ַ�� ��ַ�� ���ݸ� ���ݵ� У��� У���

    cmd[0] = id; // modbus_id

    cmd[1] = 0x02; // ������

    cmd[2] = (addr >> 8) & 0xFF; // ��ַ��
    cmd[3] = (addr >> 0) & 0xFF; // ��ַ��

    cmd[4] = 0x00; // ���ݸ�
    cmd[5] = 0x01; // ���ݵ�

    uint16_t crcvalue = usMBCRC16(cmd, 6);
    cmd[6] = (crcvalue >> 0) & 0xFF; // У���
    cmd[7] = (crcvalue >> 8) & 0xFF; // У���

    Int_Modbus_Send(cmd, 8); // ��������
}

// Modbus��Ӧ�ṹ��
typedef struct
{
    uint8_t modbus_id;
    uint8_t *status;
    uint8_t *measure;
}Modbus_Response_t;
void Int_Modbus_ResponseParse(uint8_t *data,uint16_t len)
{
    // ����Modbus��Ӧ�ṹ��
    Modbus_Response_t modbus_response;
    uint8_t message_str[100];   // �����ʽ������ַ���

    // �Խ��յ������ݽ��� CRCУ��
    uint16_t crcvalue = usMBCRC16(data, len - 2);
    uint16_t crcvalue_recv = (data[len - 1] << 8) | data[len - 2];
    if (crcvalue != crcvalue_recv)
    {
        DEBUG_PRINTLN("Modbus ��Ӧ����У��ʧ��!!!");
        return;
    }

    // ��ȡ modbus_id
    uint8_t modbus_id = data[0];
    DEBUG_PRINTLN("modbus_id = %02X",modbus_id);
    modbus_response.modbus_id = modbus_id;      //��Ӧ�ṹ�帳ֵ

    // �жϹ�����
    switch (data[1])
    {
    case 0x01:
        // ��ȡ��Ȧ ��Ӧ���ݸ�ʽ:id ������ �����ֽ��� ���� У��� У���
        if (data[3] == 0x00)
        {
            DEBUG_PRINTLN("�����ֹͣ״̬");
            modbus_response.measure = "motor is STOP status";
            modbus_response.status = "STOP";
        }
        else
        {
            DEBUG_PRINTLN("���������״̬");
            modbus_response.measure = "motor is RUN status";
            modbus_response.status = "RUN";
        }
        
        break;
    case 0x06:
        // д�뱣�ּĴ��� ��Ӧ���ݸ�ʽ:id ������ ��ַ�� ��ַ�� ���ݸ� ���ݵ� У��� У���
        DEBUG_PRINTLN("���õĵ��ת��Ϊ:%d",((data[4] << 8) | data[5]) - 500);
        sprintf((char *)message_str,"set motor speed is %d",((data[4] << 8) | data[5]) - 500);
        modbus_response.measure = message_str;
        modbus_response.status = "SET";

        break;
    case 0x04:
        // ��ȡ����Ĵ��� ��Ӧ���ݸ�ʽ:id ������ �����ֽ��� ���� У��� У���
        DEBUG_PRINTLN("�����ʵ��ת��Ϊ:%d",((data[3] << 8) | data[4]) - 500);
        sprintf((char *)message_str,"motor speed is %d",((data[3] << 8) | data[4]) - 500);
        modbus_response.measure = message_str;
        modbus_response.status = "READ";

        break;
    case 0x02:
        // ��ȡ��ɢ�� ��Ӧ���ݸ�ʽ:id ������ �����ֽ��� ���� У��� У���
        if (data[3] == 0x00)
        {
            DEBUG_PRINTLN("�������ʱ����ת");
            modbus_response.measure = "motor is anticlockwise rotation";
            modbus_response.status = "ANTI";

        }
        else
        {
            DEBUG_PRINTLN("�����˳ʱ����ת");
            modbus_response.measure = "motor is clockwise rotation";
            modbus_response.status = "CLOCK";
        }

        break;
    case 0x05:
        // д����Ȧ ��Ӧ���ݸ�ʽ:id ������ ��ַ�� ��ַ�� ���ݸ� ���ݵ� У��� У���
        if (data[4] == 0x00)
        {
            DEBUG_PRINTLN("�رյ��");
            modbus_response.measure = "close motor";
            modbus_response.status = "CLOSE";
        }
        else
        {
            DEBUG_PRINTLN("�򿪵��");
            modbus_response.measure = "open motor";
            modbus_response.status = "OPEN";
        }
        break;
    }

    // DEBUG_PRINTLN("modbus_id: %d ,status: %s ,measure: %s",modbus_response.modbus_id,modbus_response.status,modbus_response.measure);

    // ͨ�� cJSON ��ʽ������
    cJSON *json = cJSON_CreateObject();
    cJSON_AddNumberToObject(json, "modbus_id", modbus_response.modbus_id);
    cJSON_AddStringToObject(json, "status", (char *)modbus_response.status);
    cJSON_AddStringToObject(json, "measure", (char *)modbus_response.measure);

    // ת��Ϊ�ַ���
    char *json_str = cJSON_Print(json);
    if (json_str != NULL)
    {
        // DEBUG_PRINTLN("JSON �ַ���: %s", json_str);
        // ���� JSON �ַ��� �� MQTT ������
        Int_MQTT_SendToServer((uint8_t *)"112233",(uint8_t *)json_str, strlen(json_str));
        // �ͷ��ڴ�
        free(json_str);
        cJSON_Delete(json);
    }
}

