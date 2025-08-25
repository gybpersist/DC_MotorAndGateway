#ifndef __APP_EEPROM_H__
#define __APP_EEPROM_H__

#include "Int_M24C02.h"
#include "Com_Define.h"

/**
 * @brief 保存 ModbusID 到 EEPROM
 * 
 */
void App_EEPROM_SaveModbusID(void);

/**
 * @brief 从 EEPROM 加载 ModbusID
 * 
 * @note  如果没有保存过,则加载默认值 ModbusID = 1 ;已经保存过,则加载保存的值
 * @note  加载后,会自动保存到全局变量 g_motor_id 中

 */
void App_EEPROM_LoadModbusID(void);

#endif /* __APP_EEPROM_H__ */
