#include "Int_OLED.h"
#include "Int_font.h"

uint8_t OLED_GRAM[144][8];

// �� OLED дһ���ֽ�����
void Inf_OLED_WR_Byte(uint8_t dat, uint8_t mode)
{
    uint8_t tx_data[2];
    tx_data[0] = (mode == OLED_CMD) ? 0x00 : 0x40;
    tx_data[1] = dat;
    HAL_I2C_Master_Transmit(&hi2c2, OLED_I2C_ADDRESS, tx_data, 2, 100);
}

/**
 * @brief ���� OLED ��ʾ������ɫ��ʾģʽ
 *
 * �ú���ͨ������һ������ i ������ OLED ��ʾ������������ɫ��ʾ���Ƿ�ɫ��ʾ��
 * ������ɫ��ʾģʽ�£���ʾ�����������źŵ�ԭʼ��ɫ��ʾ���ݡ�
 * ��ɫ��ʾģʽ�£���ʾ���Ὣ�����źŵ���ɫ���з�ת����ʾ���ݡ�
 *
 * @param i ������ʾģʽ�Ĳ�����0 ����������ɫ��ʾ��1 ����ɫ��ʾ��
 */
void Inf_OLED_ColorTurn(uint8_t i)
{
    if (i == 0)
    {
        Inf_OLED_WR_Byte(0xA6, OLED_CMD); // ������ɫ��ʾ
    }
    if (i == 1)
    {
        Inf_OLED_WR_Byte(0xA7, OLED_CMD); // ��ɫ��ʾ
    }
}

/**
 * @brief ���� OLED ��ʾ���ķ���
 *
 * ������ͨ�����Ͳ�ͬ����� OLED ��ʾ������ʵ����Ļ��ʾ����ĵ�����
 * ��֧��������ʾ����������ʾ�ͷ�ת��ʾ��
 *
 * @param i ��ʾ������Ʋ�����0 ��ʾ������ʾ��1 ��ʾ��ת��ʾ��
 */
void Inf_OLED_DisplayTurn(uint8_t i)
{
    if (i == 0)
    {
        Inf_OLED_WR_Byte(0xC8, OLED_CMD); // ������ʾ����Ϊ������ʾ
        Inf_OLED_WR_Byte(0xA1, OLED_CMD);
    }
    if (i == 1)
    {
        Inf_OLED_WR_Byte(0xC0, OLED_CMD); // ������ʾ����Ϊ��ת��ʾ
        Inf_OLED_WR_Byte(0xA0, OLED_CMD);
    }
}

/**
 * ���� OLED ��ʾ
 * �ú���ͨ�������ض����������������� OLED ��ʾ���Ĺ���
 */
void Inf_OLED_DisPlay_On(void)
{
    Inf_OLED_WR_Byte(0x8D, OLED_CMD); // ���� OLED ����ʾ����Ƶ��
    Inf_OLED_WR_Byte(0x14, OLED_CMD); // ���� OLED ����ʾ����
    Inf_OLED_WR_Byte(0xAF, OLED_CMD); // �� OLED ��ʾ
}

/**
 * �ر� OLED ��ʾ
 *
 * ������ͨ�������ض��������������ر� OLED ��ʾ������ʾ����
 * �����ȼ�������ģʽ��Ȼ���͹ر���ʾ������
 */
void Inf_OLED_DisPlay_Off(void)
{
    Inf_OLED_WR_Byte(0x8D, OLED_CMD); // ���� OLED ������ģʽ��׼�����Ϳ���ָ��
    Inf_OLED_WR_Byte(0x10, OLED_CMD); // ���������Թر� OLED �ĳ��ã�������ʾ�رչ��̵�һ����
    Inf_OLED_WR_Byte(0xAE, OLED_CMD); // ���͹ر���ʾ�����ִ�йر� OLED ��ʾ�Ĳ���
}

/**
 * Inf_OLED_Refresh ��������ˢ�� OLED ��Ļ��ʾ��
 * �ú���ͨ���� OLED ����ָ������ݣ���������Ļ�ϵ���ʾ���ݡ�
 */
void Inf_OLED_Refresh(void)
{
    uint8_t i, n;
    for (i = 0; i < 8; i++)
    {
        Inf_OLED_WR_Byte(0xb0 + i, OLED_CMD); // ��ʼ��ҳ��ַ
        Inf_OLED_WR_Byte(0x00, OLED_CMD);     // �����е�ַ�� 4 λ
        Inf_OLED_WR_Byte(0x10, OLED_CMD);     // �����е�ַ�� 4 λ
        for (n = 0; n < 128; n++)
        {
            Inf_OLED_WR_Byte(OLED_GRAM[n][i], OLED_DATA);
        }
    }
}

/**
 * ��� OLED ��Ļ����ʾ���ݡ�
 *
 * ������ͨ���� OLED ��ͼ�� RAM��GRAM���е�������������Ϊ 0 ��ʵ����Ļ��ա�
 * ���� OLED ��Ļ����ʾ�ǻ��� GRAM �е����ݣ������� GRAM ����Ļ���ݽ�����ա�
 * �������ղ����󣬵��� Inf_OLED_Refresh ������ˢ����Ļ��ʹ���Ч����ʾ������
 */
void Inf_OLED_Clear(void)
{
    uint8_t i, n;
    for (i = 0; i < 8; i++)
    {
        for (n = 0; n < 128; n++)
        {
            OLED_GRAM[n][i] = 0;
        }
    }
    Inf_OLED_Refresh();
}

/**
 * �� OLED ��ʾ���ϻ��Ƶ������ص�
 *
 * @param x �����꣬��ʾ���ص��� OLED ��ʾ���ϵĵ� x ��
 * @param y �����꣬��ʾ���ص��� OLED ��ʾ���ϵĵ� y ��
 * @param t ������ͣ�1 ��ʾ����ǰ��ɫ�㣬0 ��ʾ���Ʊ���ɫ��
 *
 * �˺���ͨ������ OLED �� GRAM��ͼ�������ȡ�洢������ʵ�����ص�Ļ���
 * ���� OLED ��ʾ���� GRAM ��λ��ַ able �ģ�ÿ���ֽڴ��� 8 �����ص㣬�����Ҫͨ������ȷ�����ص�ľ���λ��
 */
void Inf_OLED_DrawPoint(uint8_t x, uint8_t y, uint8_t t)
{
    uint8_t i, m, n;
    i = y / 8;
    m = y % 8;
    n = 1 << m;
    if (t)
    {
        OLED_GRAM[x][i] |= n;
    }
    else
    {
        OLED_GRAM[x][i] = ~OLED_GRAM[x][i];
        OLED_GRAM[x][i] |= n;
        OLED_GRAM[x][i] = ~OLED_GRAM[x][i];
    }
}

/**
 * @brief ����ֱ��
 *
 * �ú���ʹ�� Bresenham �㷨�� OLED ��Ļ�ϻ���һ���� (x1, y1) �� (x2, y2) ��ֱ�ߡ�
 *
 * @param x1 ���� x ����
 * @param y1 ���� y ����
 * @param x2 �յ�� x ����
 * @param y2 �յ�� y ����
 * @param mode ����ģʽ�������Ǹ���ģʽ�����ģʽ
 */
void Inf_OLED_DrawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t mode)
{
    uint16_t t;
    int xerr = 0, yerr = 0, delta_x, delta_y, distance;
    int incx, incy, uRow, uCol;

    delta_x = x2 - x1;
    delta_y = y2 - y1;

    uRow = x1;
    uCol = y1;

    if (delta_x > 0)
        incx = 1;
    else if (delta_x == 0)
        incx = 0;
    else
    {
        incx = -1;
        delta_x = -delta_x;
    }

    if (delta_y > 0)
        incy = 1;
    else if (delta_y == 0)
        incy = 0;
    else
    {
        incy = -1;
        delta_y = -delta_y;
    }

    if (delta_x > delta_y)
        distance = delta_x;
    else
        distance = delta_y;

    for (t = 0; t < distance + 1; t++)
    {
        Inf_OLED_DrawPoint(uRow, uCol, mode);
        xerr += delta_x;
        yerr += delta_y;
        if (xerr > distance)
        {
            xerr -= distance;
            uRow += incx;
        }
        if (yerr > distance)
        {
            yerr -= distance;
            uCol += incy;
        }
    }
}

/**
 * @brief ����Բ
 *
 * �ú���ʹ���е㻭Բ������һ��Բ���е㻭Բ����һ����Ч�Ļ���Բ���㷨����������Բ�İ˶Գ��ԣ�
 * ͨ������Բ��һ���㣬���Եõ������߸����λ�á����ַ��������˼�����������˻�ͼЧ�ʡ�
 *
 * @param x Բ�ĵ� x ����
 * @param y Բ�ĵ� y ����
 * @param r Բ�İ뾶
 */
void Inf_OLED_DrawCircle(uint8_t x, uint8_t y, uint8_t r)
{
    int a, b, num;
    a = 0;
    b = r;

    while (2 * b * b >= r * r)
    {
        Inf_OLED_DrawPoint(x + a, y - b, 1);
        Inf_OLED_DrawPoint(x - a, y - b, 1);
        Inf_OLED_DrawPoint(x - a, y + b, 1);
        Inf_OLED_DrawPoint(x + a, y + b, 1);

        Inf_OLED_DrawPoint(x + b, y + a, 1);
        Inf_OLED_DrawPoint(x + b, y - a, 1);
        Inf_OLED_DrawPoint(x - b, y - a, 1);
        Inf_OLED_DrawPoint(x - b, y + a, 1);

        a++;
        num = (a * a + b * b) - r * r;
        if (num > 0)
        {
            b--;
            a--;
        }
    }
}

/**
 * @brief �� OLED ����ʾһ���ַ�
 *
 * �ú��������� OLED ��Ļ����ʾһ���ַ������Ը��ݲ����Ĳ�ͬ�����ַ��Ĵ�С����ʾģʽ��
 *
 * @param x �ַ���ʾ����ʼ X ����
 * @param y �ַ���ʾ����ʼ Y ����
 * @param chr Ҫ��ʾ���ַ�
 * @param size1 �ַ��Ĵ�С��֧�� 8, 12, 16, 24 ����
 * @param mode ��ʾģʽ��0 Ϊ��ɫ��1 Ϊ��ɫ
 */
void Inf_OLED_ShowChar(uint8_t x, uint8_t y, uint8_t chr, uint8_t size1, uint8_t mode)
{
    uint8_t i, m, temp, size2, chr1;
    uint8_t x0 = x, y0 = y;
    if (size1 == 8)
        size2 = 6;
    else
        size2 = (size1 / 8 + ((size1 % 8) ? 1 : 0)) * (size1 / 2);
    chr1 = chr - ' ';
    for (i = 0; i < size2; i++)
    {
        if (size1 == 8)
            temp = asc2_0806[chr1][i];
        else if (size1 == 12)
            temp = asc2_1206[chr1][i];
        else if (size1 == 16)
            temp = asc2_1608[chr1][i];
        else if (size1 == 24)
            temp = asc2_2412[chr1][i];
        else
            return;
        for (m = 0; m < 8; m++)
        {
            if (temp & 0x01)
                Inf_OLED_DrawPoint(x, y, mode);
            else
                Inf_OLED_DrawPoint(x, y, !mode);
            temp >>= 1;
            y++;
        }
        x++;
        if ((size1 != 8) && ((x - x0) == size1 / 2))
        {
            x = x0;
            y0 = y0 + 8;
        }
        y = y0;
    }
}

/**
 * @brief �� OLED ����ʾ�ַ���
 *
 * �ú��������� OLED ��ʾ������ʾһ���ַ�������������ṩ�Ĳ��������ַ�����λ�úʹ�С��������ַ���ʾ��
 *
 * @param x �ַ�����ʾ����ʼ X ����
 * @param y �ַ�����ʾ����ʼ Y ����
 * @param chr ָ��Ҫ��ʾ���ַ�����ָ��
 * @param size1 �ַ��Ĵ�С���������ַ�����Ļ�ϵĿ��
 * @param mode ��ʾģʽ�����ܾ������ַ�����ɫ����ʾЧ��
 */
void Inf_OLED_ShowString(uint8_t x, uint8_t y,uint8_t *chr, uint8_t size1, uint8_t mode)
{
    // �����ַ�������
    uint16_t len = strlen((char *)chr);
    for (uint16_t i = 0; i < len; i++)
    {
        Inf_OLED_ShowChar(x, y, chr[i], size1, mode);
        if (size1 == 8)
        {
            x += 6;
        }
        else
        {
            x += size1 / 2;
        }
    }
}

/**
 * ���� m �� n ����
 *
 * �˺���ʹ��ָ������������һ�������ݴΡ�����Ҫ������ OLED ��ʾ�����н���ĳЩ���㣬
 * ����ʵ���� OLED ��ʾ������ֱ�ӹ�������������һ����ѧ�ݴμ��㡣
 *
 * @param m ������������Ҫ�������ݴε�����
 * @param n ָ������ʾ�����Գ˵Ĵ���
 * @return ���� m �� n ���ݵĽ��
 *
 * ѡ��ʹ��ѭ�����ǵݹ���ʵ�֣��Ա���ջ������գ������ִ��Ч��
 */
uint32_t Inf_OLED_Pow(uint8_t m, uint8_t n)
{
    uint32_t result = 1;
    while (n--)
    {
        result *= m;
    }
    return result;
}

/**
 * �� OLED ��ʾ������ʾ����
 *
 * @param x ������ʾ����ʼ������
 * @param y ������ʾ����ʼ������
 * @param num Ҫ��ʾ������
 * @param len ������ʾ�ĳ��ȣ����㲿�ֻ���ʾΪ 0
 * @param size1 ������ʾ�������С��8 ��ʾ�� 8��������ֵ��ʾ�� 16 ����
 * @param mode ��ʾģʽ��������ɫ
 *
 * �˺��������� OLED ��Ļ����ָ����λ�á���С�ͳ�����ʾһ������
 * ����������ֵ�λ����ָ���ĳ��ȣ��Զ���ǰ�油��
 * ���ҿ��Ը��������С�������ּ�ļ��
 */
void Inf_OLED_ShowNum(uint8_t x, uint8_t y, uint32_t num, uint8_t len, uint8_t size1, uint8_t mode)
{
    uint8_t t, temp, m = 0;
    // ���������С�������ּ�Ķ�����
    if (size1 == 8)
        m = 2;
    for (t = 0; t < len; t++)
    {
        // ���㵱ǰλ������
        temp = (num / Inf_OLED_Pow(10, len - t - 1)) % 10;
        if (temp == 0)
        {
            // �����ǰλΪ 0����ʾ�ַ� '0'
            Inf_OLED_ShowChar(x + (size1 / 2 + m) * t, y, '0', size1, mode);
        }
        else
        {
            // �����ǰλ��Ϊ 0����ʾ��Ӧ���ַ�
            Inf_OLED_ShowChar(x + (size1 / 2 + m) * t, y, temp + '0', size1, mode);
        }
    }
}

/**
 * @brief ��ʾ�����ַ�
 *
 * �ú��������� OLED ��Ļ����ʾһ�������ַ��������ݸ����Ĳ�����λ��ʾλ�ã�
 * ѡ���ַ��ʹ�С��������ָ��ģʽ�����ַ�����
 *
 * @param x ��ʼ��ʾ�� x ����
 * @param y ��ʼ��ʾ�� y ����
 * @param num �ַ���ţ����������ֿ�
 * @param size1 �ַ���С��Ŀǰֻ֧�� 16x16 ����
 * @param mode ����ģʽ�����������ʾ��ʽ
 */
void Inf_OLED_ShowChinese(uint8_t x, uint8_t y, uint8_t num, uint8_t size1, uint8_t mode)
{
    uint8_t m, temp;
    uint8_t x0 = x, y0 = y;
    // ����һ�����ֶ�Ӧ����������ȷ���ܹ�������ʾһ�����ֵĵ�����Ϣ
    uint16_t i, size3 = (size1 / 8 + ((size1 % 8) ? 1 : 0)) * size1;
    for (i = 0; i < size3; i++)
    {
        // Ŀǰֻ���� 16 ����ĺ��֣�������С��֧��
        if (size1 == 16)
            temp = Hzk1[num][i]; // ��ȡ��ǰ�ֽڵĵ�������
        else
            return;
        for (m = 0; m < 8; m++)
        {
            // ���ݵ������ݻ���ÿ���㣬�����ʾȡ���� temp �����λ�� mode
            if (temp & 0x01)
                Inf_OLED_DrawPoint(x, y, mode);
            else
                Inf_OLED_DrawPoint(x, y, !mode);
            temp >>= 1; // ����һλ��׼��������һ����
            y++;
        }
        x++;
        // ÿ������һ�е����������� x �� y ���꣬��׼��������һ��
        if ((x - x0) == size1)
        {
            x = x0;
            y0 = y0 + 8;
        }
        y = y0;
    }
}

/**
 * @brief ������ʾ�����ַ�
 *
 * �ú��������� OLED ��ʾ���Ϲ�����ʾ�����ַ���ͨ��������ʾ�����ݡ��������ٶȺ���ʾģʽ��ʵ�ֶ�̬��ʾЧ����
 *
 * @param num ��ʾ�������ַ�����
 * @param space �ַ�֮��ļ��
 * @param mode ��ʾģʽ�������ַ�����ɫ�����磬��ɫ���ɫ��
 */
void Inf_OLED_ScrollDisplay(uint8_t num, uint8_t space, uint8_t mode)
{
    uint8_t i, n, t = 0, m = 0, r;
    while (1)
    {
        if (m == 0)
        {
            // ��ʾһ�������ַ��� OLED ��ʾ���ϣ�λ����(128, 24)���ֺ�Ϊ 16 ���󣬰���ָ������ʾģʽ
            Inf_OLED_ShowChinese(128, 24, t, 16, mode);
            t++;
        }
        if (t == num)
        {
            // �����ַ�����֮ǰ����ͣ��ͨ�������ʾ��������һ������ʵ��
            for (r = 0; r < 16 * space; r++)
            {
                for (i = 1; i < 144; i++)
                {
                    for (n = 0; n < 8; n++)
                    {
                        OLED_GRAM[i - 1][n] = OLED_GRAM[i][n];
                    }
                }
                // ˢ�� OLED ��ʾ����
                Inf_OLED_Refresh();
            }
            t = 0;
        }
        m++;
        if (m == 16)
            m = 0;
        // ʵ�ֹ���Ч��������ʾ��������������ǰ�ƶ�
        for (i = 1; i < 144; i++)
        {
            for (n = 0; n < 8; n++)
            {
                OLED_GRAM[i - 1][n] = OLED_GRAM[i][n];
            }
        }
        // ˢ�� OLED ��ʾ����
        Inf_OLED_Refresh();
    }
}

/**
 * �� OLED ��ʾ������ʾͼƬ
 *
 * @param x ͼƬ��ʾ����ʼ x ����
 * @param y ͼƬ��ʾ����ʼ y ����
 * @param sizex ͼƬ�Ŀ��
 * @param sizey ͼƬ�ĸ߶�
 * @param BMP ͼƬ����������
 * @param mode ����ģʽ��0 Ϊ��ɫ��1 Ϊ��ɫ
 *
 * �˺���ͨ�������Ƶķ�ʽ�� OLED ��Ļ����ʾһ��ͼƬ
 * �������ṩ��ͼƬ���������ָ������ʾ�����������еؽ���ͼƬ����
 * ������ͼƬ�����е�ÿһλ��ȷ���Ƿ�����Ļ�ϻ��Ƶ�
 */
void Inf_OLED_ShowPicture(uint8_t x, uint8_t y, uint8_t sizex, uint8_t sizey, uint8_t BMP[], uint8_t mode)
{
    // ��ʼ������ j Ϊ 0�����ڱ���ͼƬ��������
    uint16_t j = 0;
    // ������� i,n,temp,m �����ڲ�ѭ�������ݴ���
    uint8_t i, n, temp, m;
    // ������ʼ���꣬���ں��������긴λ
    uint8_t x0 = x, y0 = y;
    // ����ͼƬ�ĸ߶ȣ����ǵ�ÿ���ֽڴ��� 8 ������
    sizey = sizey / 8 + ((sizey % 8) ? 1 : 0);
    // ���ѭ������ͼƬ��ÿһ��
    for (n = 0; n < sizey; n++)
    {
        // �в�ѭ������ͼƬ��ÿһ��
        for (i = 0; i < sizex; i++)
        {
            // ��ȡ��ǰ�е�ͼƬ����
            temp = BMP[j];
            j++;
            // �ڲ�ѭ������ÿ�����ص�
            for (m = 0; m < 8; m++)
            {
                // ����ͼƬ���ݵ�ÿһλ�����Ƿ���Ƶ�
                if (temp & 0x01)
                    Inf_OLED_DrawPoint(x, y, mode);
                else
                    Inf_OLED_DrawPoint(x, y, !mode);
                // ��λ�Դ�����һλ����
                temp >>= 1;
                y++;
            }
            x++;
            // ���ﵽͼƬ���ʱ������ x ���겢���� y ����
            if ((x - x0) == sizex)
            {
                x = x0;
                y0 = y0 + 8;
            }
            y = y0;
        }
    }
}

// ��ʼ�� OLED ��ʾ��
void Inf_OLED_Init(void)
{
    // �ӳ� 800ms��ȷ�� OLED ��ʾ�����㹻��ʱ������
    HAL_Delay(800);

    // ����һϵ�г�ʼ����� OLED ��ʾ��
    Inf_OLED_WR_Byte(0xAE, OLED_CMD); // --turn off oled panel
    Inf_OLED_WR_Byte(0x00, OLED_CMD); // ---set low column address
    Inf_OLED_WR_Byte(0x10, OLED_CMD); // ---set high column address
    Inf_OLED_WR_Byte(0x40, OLED_CMD); // --set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
    Inf_OLED_WR_Byte(0x81, OLED_CMD); // --set contrast control register
    Inf_OLED_WR_Byte(0xCF, OLED_CMD); // Set SEG Output Current Brightness
    Inf_OLED_WR_Byte(0xA1, OLED_CMD); // --Set SEG/Column Mapping     0xa0 ��ת 0xa1 ����
    Inf_OLED_WR_Byte(0xC8, OLED_CMD); // Set COM/Row Scan Direction   0xc0 ��ת 0xc8 ����
    Inf_OLED_WR_Byte(0xA6, OLED_CMD); // --set normal display
    Inf_OLED_WR_Byte(0xA8, OLED_CMD); // --set multiplex ratio(1 to 64)
    Inf_OLED_WR_Byte(0x3f, OLED_CMD); // --1/64 duty
    Inf_OLED_WR_Byte(0xD3, OLED_CMD); // -set display offset    Shift Mapping RAM Counter (0x00~0x3F)
    Inf_OLED_WR_Byte(0x00, OLED_CMD); // -not offset
    Inf_OLED_WR_Byte(0xd5, OLED_CMD); // --set display clock divide ratio/oscillator frequency
    Inf_OLED_WR_Byte(0x80, OLED_CMD); // --set divide ratio, Set Clock as 100 Frames/Sec
    Inf_OLED_WR_Byte(0xD9, OLED_CMD); // --set pre-charge period
    Inf_OLED_WR_Byte(0xF1, OLED_CMD); // Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
    Inf_OLED_WR_Byte(0xDA, OLED_CMD); // --set com pins hardware configuration
    Inf_OLED_WR_Byte(0x12, OLED_CMD);
    Inf_OLED_WR_Byte(0xDB, OLED_CMD); // --set vcomh
    Inf_OLED_WR_Byte(0x40, OLED_CMD); // Set VCOM Deselect Level
    Inf_OLED_WR_Byte(0x20, OLED_CMD); // -Set Page Addressing Mode (0x00/0x01/0x02)
    Inf_OLED_WR_Byte(0x02, OLED_CMD); //
    Inf_OLED_WR_Byte(0x8D, OLED_CMD); // --set Charge Pump enable/disable
    Inf_OLED_WR_Byte(0x14, OLED_CMD); // --set(0x10) disable
    Inf_OLED_WR_Byte(0xA4, OLED_CMD); // Disable Entire Display On (0xa4/0xa5)
    Inf_OLED_WR_Byte(0xA6, OLED_CMD); // Disable Inverse Display On (0xa6/a7)
    // ��� OLED ��ʾ���ϵ���������
    Inf_OLED_Clear();
    // ������������� OLED ���
    Inf_OLED_WR_Byte(0xAF, OLED_CMD);
}
