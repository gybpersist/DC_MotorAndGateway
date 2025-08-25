#include "Com_Util.h"

void Com_Delay_us(uint16_t us)
{
    volatile uint32_t count = 72 * us / 9;
    while(count--)
    {
        __NOP();
    }
}

void Com_Delay_ms(uint16_t ms)
{
    HAL_Delay(ms);
}

void Com_UTC2LocalTime(uint8_t *utc_time, uint8_t *local_time)
{
    struct tm utc_tm;       //���� UTC ʱ��ṹ�� ,���� UTC ʱ��
    struct tm *local_tm;     //���屾��ʱ��ṹ��ָ�� ,���汾��ʱ��

    // �� UTC ʱ���ַ���ת��Ϊ UTC ʱ��ṹ��
    sscanf((char *)utc_time, "%04d-%02d-%02d %02d:%02d:%02d", &utc_tm.tm_year, &utc_tm.tm_mon, &utc_tm.tm_mday, &utc_tm.tm_hour, &utc_tm.tm_min, &utc_tm.tm_sec);
    // ������ݺ��·�
    utc_tm.tm_year -= 1900;
    utc_tm.tm_mon -= 1;
    // �� UTC ʱ��ṹ��ת��Ϊʱ���
    time_t timestamp = mktime(&utc_tm);
    // ��ʱ������� 8 Сʱ ,��ɱ���ʱ���ʱ���
    timestamp += 8 * 60 * 60;
    // ��ʱ���ת��Ϊ����ʱ��ṹ��
    local_tm = localtime(&timestamp);
    // ������ʱ��ṹ��ת��Ϊ�ַ���  YYYY-MM-DD HH:MM:SS ��ʽ
    sprintf((char *)local_time, "%04d-%02d-%02d %02d:%02d:%02d", local_tm->tm_year + 1900, local_tm->tm_mon + 1, local_tm->tm_mday, local_tm->tm_hour, local_tm->tm_min, local_tm->tm_sec);
}
