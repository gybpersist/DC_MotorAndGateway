#ifndef __INT_MODBUS_H__
#define __INT_MODBUS_H__

#include "usart.h"
#include "Com_Debug.h"
#include "mbcrc.h"
#include "cJSON.h"
#include <stdlib.h>  // ���ͷ�ļ�������free����������
#include "Int_W5500.h" 

/**
 * @brief Modbus ��������
 * 
 * @param data Ҫ���͵�����
 * @param len ���ݳ���
 */
void Int_Modbus_Send(uint8_t *data, uint16_t len);

/**
 * @brief Modbus д��Ȧ ������:0x05
 * 
 * @param id modbus_id
 * @param addr д����Ȧ�ĵ�ַ
 * @param value Ҫд���ֵ [0:�ر� 1:����]
 */
void Int_Modbus_WriteCoil(uint8_t id,uint16_t addr,uint8_t value);

/**
 * @brief Modbus ����Ȧ ������:0x01
 * 
 * @param id modbus_id
 * @param addr ��ȡ��Ȧ�ĵ�ַ
 */
void Int_Modbus_ReadCoil(uint8_t id,uint16_t addr);

/**
 * @brief Modbus д���ּĴ��� ������:0x06
 * 
 * @param id modbus_id
 * @param addr д�뱣�ּĴ����ĵ�ַ
 * @param value Ҫд���ֵ
 */
void Int_Modbus_WriteHOLD(uint8_t id,uint16_t addr,uint16_t value);

/**
 * @brief Modbus ������Ĵ��� ������:0x04
 * 
 * @param id modbus_id
 * @param addr ��ȡ����Ĵ����ĵ�ַ
 */
void Int_Modbus_ReadINPUT(uint8_t id,uint16_t addr);

/**
 * @brief Modbus ����ɢ�� ������:0x02
 * 
 * @param id modbus_id
 * @param addr ��ȡ��ɢ���ĵ�ַ
 */
void Int_Modbus_ReadDISC(uint8_t id,uint16_t addr);

/**
 * @brief ���յ� Modbus��Ϣ ��Ӧ
 * 
 * @param data ��Ӧ����
 * @param len ���ݳ���
 */
void Int_Modbus_ResponseParse(uint8_t *data,uint16_t len);

#endif /* __INT_MODBUS_H__ */
