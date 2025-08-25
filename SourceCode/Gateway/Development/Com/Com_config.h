#ifndef __COM_CONFIG_H__
#define __COM_CONFIG_H__

#include <stdint.h>

// ����ṹ�� ���汾�� IP��ַ.MAC��ַ.��������.���ص�ַ
typedef struct
{
    uint8_t ip[4];  // IP��ַ
    uint8_t mac[6]; // MAC��ַ
    uint8_t snm[4]; // ��������
    uint8_t gw[4];  // ���ص�ַ
} Com_LocalConfig_t;



#endif /* __COM_CONFIG_H__ */
