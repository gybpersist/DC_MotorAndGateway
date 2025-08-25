#include "Int_W5500.h"

// ����� socket ��� (��ѡ sn=1~7)
#define SOCKET_SN 0
// ����� ���ض˿ں�
#define LOCAL_PORT 8457

// ����� �������˿ں�
#define SERVER_PORT 1883
// ���� ������ IP ��ַ
uint8_t server_ip[4] = {192,168,11,31};

// ���� �������ṹ��ָ��
Network network;
// ���� mqttclient �ͻ���
MQTTClient mqttclient;
// ���� MQTT���ͻ�����
uint8_t mqtt_sendbuf[1024];
// ���� MQTT���ջ�����
uint8_t mqtt_readbuf[1024];

/**
 * ���ݱ�ʾ:
 * id: 1 ���õ������ͣ
 * id: 2 ��ȡ�������ͣ
 * id: 3 ���õ����ת��
 * id: 4 ��ȡ�����ʵ��ת��
 * id: 5 ��ȡ�������ת����
 */
// ���� ���� aabbcc �Ļص�����
void mqtt_aabbcc_callback(MessageData* messagedata)
{
    DEBUG_PRINTLN("���ն��� aabbcc �ɹ�......");
    // debug_printfln("���յ�����:%s", messagedata->message->payload);

    // 1 ���յ��� cjson�ַ��� ����Ϊ cjson���� 
    cJSON *root = cJSON_ParseWithLength(messagedata->message->payload,messagedata->message->payloadlen);

    // 2 �ӽ������� cjson���� �н���ÿһ���ֶ�
    cJSON *id = cJSON_GetObjectItem(root,"id");
    cJSON *connect_type = cJSON_GetObjectItem(root,"connect_type");
    cJSON *modbus_id = cJSON_GetObjectItem(root,"modbus_id");
    

    // 3 �� cjson���� �л�ȡ�ַ���
    int id_int = id->valueint;
    char *connect_type_str = connect_type->valuestring;
    int modbus_id_int = modbus_id->valueint;
    

    // 4 �����͵��ж�
    if (!cJSON_IsNumber(id) || !cJSON_IsString(connect_type) || !cJSON_IsNumber(modbus_id))
    {
        DEBUG_PRINTLN("id �� connect_type �� modbus_id ���ʹ���!!!");
        cJSON_Delete(root);
        return;
    }

    DEBUG_PRINTLN("id = %d,connect_type = %s,modbus_id = %d  ",id_int,connect_type_str,modbus_id_int);

    // 5 ���� id ����ͬ�Ĵ���
    if (id_int == 1)
    {
        // ���õ������ͣ
        cJSON *on = cJSON_GetObjectItem(root,"on");
        int on_int = on->valueint;
        DEBUG_PRINTLN("���õĵ����ͣ״̬Ϊ:%d",on_int);

        Int_Modbus_WriteCoil(modbus_id_int,2,(on_int == 1) ? 1 : 0);
    }
    else if (id_int == 2)
    {
        // ��ȡ�������ͣ
        Int_Modbus_ReadCoil(modbus_id_int,2);
    }
    else if (id_int == 3)
    {
        // ���õ����ת��
        cJSON *speed = cJSON_GetObjectItem(root,"speed");
        int speed_int = speed->valueint;
        speed_int = speed_int + 500;
        Int_Modbus_WriteHOLD(modbus_id_int,2,speed_int);
    }
    else if (id_int == 4)
    {
        // ��ȡ�����ʵ��ת��
        Int_Modbus_ReadINPUT(modbus_id_int,2);
    }
    else if (id_int == 5)
    {
        // ��ȡ�������ת����
        Int_Modbus_ReadDISC(modbus_id_int,2);
    }
    else
    {
        DEBUG_PRINTLN("id ����!!!");
    }

    // 5 �ͷ� cjson����
    cJSON_Delete(root);
}

// ���屾�����ò���
Com_LocalConfig_t LocalConfig = {
    .ip = {192,168,11,100},                       //IP��ַ
    .mac = {122, 142, 162, 120, 144, 190},    //MAC��ַ
    .snm = {255,255,255,0},                      //��������
    .gw = {192,168,11,1}                          //���ص�ַ
};

void Int_W5500_Init(void)
{
    // ����������������----------------------------------------------------------
    // 1 ��λ
    // 1.1 ���͸�λ���� W5500_RST
    HAL_GPIO_WritePin(W5500_RST_GPIO_Port, W5500_RST_Pin, GPIO_PIN_RESET);
    Com_Delay_ms(10);       //������Ҫ���� 500 us
    // 1.3 ���߸�λ���� W5500_RST
    HAL_GPIO_WritePin(W5500_RST_GPIO_Port, W5500_RST_Pin, GPIO_PIN_SET);
    Com_Delay_ms(10);       //�����ȶ�

    // 2 ע�ắ��
    development_reg_func();

    // 3 ����IP��ַ.MAC��ַ.��������.���ص�ַ
    setSIPR(LocalConfig.ip);    //����IP��ַ
    setSHAR(LocalConfig.mac);   //����MAC��ַ
    setSUBR(LocalConfig.snm);   //������������
    setGAR(LocalConfig.gw);     //�������ص�ַ

    DEBUG_PRINTLN("W5500 ��ʼ�����......");
    // ����������������----------------------------------------------------------

    // ��ʱ�ȴ��������
    HAL_Delay(2000);

    // ����TCP��������----------------------------------------------------------
    // 1 ����TCP��������
    // 1.1 ����һ���������
    NewNetwork(&network,SOCKET_SN);

    // 1.2 ���ӷ�����
    int Connect_Result = ConnectNetwork(&network,server_ip,SERVER_PORT);
    if (Connect_Result != SOCK_OK)
    {
        DEBUG_PRINTLN("���� TCP ���ӷ�����ʧ��......");
        return ;
    }
    DEBUG_PRINTLN("���� TCP ���ӷ������ɹ�......");
    // ����TCP��������----------------------------------------------------------

    // ���� MQTT ������---------------------------------------------------------
    // 1 MQTT����
    // 1.1 ���� MQTT �ͻ���
    MQTTClientInit(&mqttclient,&network,5000,(unsigned char *)mqtt_sendbuf,sizeof(mqtt_sendbuf),(unsigned char *)mqtt_readbuf,sizeof(mqtt_readbuf));
    
    // 1.2 ���� MQTT ����
    MQTTPacket_connectData options = MQTTPacket_connectData_initializer;
    options.cleansession = 1;               //����Ự
    options.clientID.cstring = "huihui";    //�ͻ���ID
    options.keepAliveInterval = 60;         //��������ʱ��
    options.MQTTVersion = 4;                //4: 3.1.1
    options.password.cstring = NULL;
    options.username.cstring = NULL;
    options.willFlag = 0;                   //û������
    int mqttresult = MQTTConnect(&mqttclient,&options);
    if(mqttresult != SUCCESSS)
    {
        DEBUG_PRINTLN("���� MQTT ����ʧ��......");
        return ;
    }
    DEBUG_PRINTLN("���� MQTT ���ӳɹ�......");
    // ���� MQTT ������---------------------------------------------------------

    // ����
    MQTTSubscribe(&mqttclient,"aabbcc",QOS0,mqtt_aabbcc_callback);
}

void Int_MQTT_Receive(void)
{
    // ��� MQTT �Ƿ�����,�Ͽ�����������
    Int_MQTT_IsConnect();

    // 2 ��ѯ��������
    MQTTYield(&mqttclient, 50);
}

void Int_MQTT_IsConnect(void)
{
    // 1 ��ȡ socket ״̬
    uint8_t connect_type = getSn_SR(SOCKET_SN);
    // 2 �ж��Ƿ����ӳɹ�
    if (connect_type != SOCK_ESTABLISHED)
    {
        DEBUG_PRINTLN("MQTT �������Ͽ�����...,������������......");
        Int_W5500_Init();
    }
}

void Int_MQTT_SendToServer(uint8_t *topic,uint8_t *data,uint16_t len)
{
    // �����Ϣ
    MQTTMessage message;
    message.qos = QOS0;
    message.payload = data;
    message.payloadlen = len;
    MQTTPublish(&mqttclient, (char *)topic, &message);
}

// uint8_t Int_W5500_SendData(uint8_t *data, uint16_t len)
// {
//     // 0 ������� ���� socket ��״̬
//     uint8_t status = 0;

//     // 1 ��鵱ǰ������״̬ ,ֱ��Ϊ ESTABLISHED ״̬
//     do
//     {
//         // 1.1 ��ȡ socket ״̬ (�ر�״̬;����YCPģʽ;�Ͽ�����)
//         status = getSn_SR(SOCKET_SN);
        
//         // 1.2 ��� socket ״̬�Ƿ�Ϊ�ر�״̬ ,���� socket �ͻ���
//         if (status == SOCK_CLOSED)
//         {
//             // 1.2.1 ���� socket �ͻ���
//             uint8_t socket_status = socket(SOCKET_SN, Sn_MR_TCP, LOCAL_PORT, 0);
//             if (socket_status == SOCKET_SN)
//             {
//                 DEBUG_PRINTLN("socket �ͻ��˴����ɹ�......");
//             }
//             else
//             {
//                 DEBUG_PRINTLN("socket �ͻ��˴���ʧ��......");
//             }
//         }

//         // 1.3 ��� socket ״̬�Ƿ�Ϊ INIT״̬ ,����� ,�����ӷ�����
//         if (status == SOCK_INIT)
//         {
//             // 1.3.1 ���ӷ�����
//             uint8_t connect_status = connect(SOCKET_SN, server_ip, SERVER_PORT);

//             if (connect_status == SOCK_OK)
//             {
//                 DEBUG_PRINTLN("socket �ͻ������ӷ������ɹ�......");
//             }
//             else
//             {
//                 DEBUG_PRINTLN("socket �ͻ������ӷ�����ʧ��......");

//             }
//         }

//         // 1.4 ��� socket ״̬�Ƿ�Ϊ CLOSE_WAIT ״̬,����� ,��ر����ӷ�����
//         if (status == SOCK_CLOSE_WAIT)
//         {
//             // 1.4.1 �ر����ӷ�����
//             uint8_t close_status = close(SOCKET_SN);
//             if (close_status == SOCK_OK)
//             {
//                 DEBUG_PRINTLN("socket �ͻ��˹ر����ӳɹ�......");
//             }
//             else
//             {
//                 DEBUG_PRINTLN("socket �ͻ��˹ر�����ʧ��......");
//             }
//         }
//     } while (status != SOCK_ESTABLISHED);
    
//     // 2 ��������
//     uint16_t send_status = send(SOCKET_SN, data, len);
//     if (send_status == len)
//     {
//         DEBUG_PRINTLN("socket �ͻ��˷������ݳɹ�......");
//         return 0;

//     }
//     else
//     {
//         DEBUG_PRINTLN("socket �ͻ��˷�������ʧ��......");
//         return 1;
//     }
// }
