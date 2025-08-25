#ifndef __APP_EEPROM_H__
#define __APP_EEPROM_H__

#include "Int_M24C02.h"
#include "Com_Define.h"

/**
 * @brief ���� ModbusID �� EEPROM
 * 
 */
void App_EEPROM_SaveModbusID(void);

/**
 * @brief �� EEPROM ���� ModbusID
 * 
 * @note  ���û�б����,�����Ĭ��ֵ ModbusID = 1 ;�Ѿ������,����ر����ֵ
 * @note  ���غ�,���Զ����浽ȫ�ֱ��� g_motor_id ��

 */
void App_EEPROM_LoadModbusID(void);

#endif /* __APP_EEPROM_H__ */
