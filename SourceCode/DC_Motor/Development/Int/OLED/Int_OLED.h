#ifndef __OLED_H__
#define __OLED_H__

#include "gpio.h"
#include "i2c.h"
#include "stdlib.h"
#include "string.h"
// I2C��ַ
#define OLED_I2C_ADDRESS 0x78

#define OLED_CMD 0  // ָ��
#define OLED_DATA 1 // ����

void Inf_OLED_ColorTurn(uint8_t i);
void Inf_OLED_DisplayTurn(uint8_t i);
void Inf_OLED_WR_Byte(uint8_t dat, uint8_t mode);
void Inf_OLED_DisPlay_On(void);
void Inf_OLED_DisPlay_Off(void);
void Inf_OLED_Refresh(void);
void Inf_OLED_Clear(void);
void Inf_OLED_DrawPoint(uint8_t x, uint8_t y, uint8_t t);
void Inf_OLED_DrawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t mode);
void Inf_OLED_DrawCircle(uint8_t x, uint8_t y, uint8_t r);
void Inf_OLED_ShowChar(uint8_t x, uint8_t y, uint8_t chr, uint8_t size1, uint8_t mode);
void Inf_OLED_ShowString(uint8_t x, uint8_t y, uint8_t *chr, uint8_t size1, uint8_t mode);
void Inf_OLED_ShowNum(uint8_t x, uint8_t y, uint32_t num, uint8_t len, uint8_t size1, uint8_t mode);
void Inf_OLED_ShowChinese(uint8_t x, uint8_t y, uint8_t num, uint8_t size1, uint8_t mode);
void Inf_OLED_ScrollDisplay(uint8_t num, uint8_t space, uint8_t mode);
void Inf_OLED_ShowPicture(uint8_t x, uint8_t y, uint8_t sizex, uint8_t sizey, uint8_t BMP[], uint8_t mode);
void Inf_OLED_Init(void);

#endif
