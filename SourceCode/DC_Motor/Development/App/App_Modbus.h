#ifndef __APP_MODBUS_H__
#define __APP_MODBUS_H__

#include "Com_Debug.h"
#include "Com_Define.h"
#include "mb.h"
#include "port.h"

/**
 * @brief ��ʼ�� Modbus ͨ��
 * 
 */
void App_Modbus_Init(void);

/**
 * @brief ���� Modbus ͨ��
 * 
 */
void App_Modbus_Handle(void);

#endif /* __APP_MODBUS_H__ */
