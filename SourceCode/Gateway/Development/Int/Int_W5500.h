#ifndef __INT_W5500_H__
#define __INT_W5500_H__

#include "wizchip_conf.h"
#include "socket.h"
#include "Com_Debug.h"
#include "Com_Util.h"
#include "Com_Config.h"
#include "mqtt_interface.h"
#include "MQTTClient.h"
#include "cJSON.h"
#include "Int_Modbus.h"


/**
 * @brief W5500��̫��ģ�� ��ʼ��

 * 
 */
void Int_W5500_Init(void);

/**
 * @brief ��ѯ����MQTT�Ķ��ĵ�����
 */
void Int_MQTT_Receive(void);

/**
 * @brief ��� MQTT �Ƿ�����,�Ͽ�����������
 * 
 */
void Int_MQTT_IsConnect(void);

/**
 * @brief ���� Modbus���ݵ�������
 * 
 * @param topic ����
 * @param data Ҫ���͵�����
 * @param len ���ݳ���
 */
void Int_MQTT_SendToServer(uint8_t *topic,uint8_t *data,uint16_t len);

/**
 * @brief W5500��̫��ģ�� �������ݵ�������
 * 
 * @param data Ҫ���͵�����
 * @param len ���ݳ���
 * @return uint8_t ����״̬ (0:�ɹ�;1:ʧ��)

 */
// uint8_t Int_W5500_SendData(uint8_t *data, uint16_t len);

#endif /* __INT_W5500_H__ */
