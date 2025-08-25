#ifndef __INT_M24C02_H__
#define __INT_M24C02_H__

#include "i2c.h"
#include "Com_Debug.h"
#include "FreeRTOS.h"
#include "task.h"

#define M24C02_ADDR 0xA0
#define M24C02_ADDR_W 0xA0
#define M24C02_ADDR_R 0xA1

/**
 * @brief ��ʼ��
 */
void Int_M24C02_Init(void);

/**
 * @brief дһ���ֽ�
 */
void Int_M24C02_WriteByte(uint8_t byte_addr, uint8_t data);

/**
 * @brief д����ֽ�
 */
void Int_M24C02_WriteBytes(uint8_t byte_addr, uint8_t *data, uint8_t len);

/**
 * @brief ��һ���ֽ�
 */
void Int_M24C02_ReadByte(int8_t byte_addr, uint8_t *data);

/**
 * @brief ������ֽ�
 */
void Int_M24C02_ReadBytes(uint8_t byte_addr, uint8_t *data, uint8_t len);

#endif /* __INT_M24C02_H__ */
