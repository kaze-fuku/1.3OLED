#ifndef __OLED_H__
#define __OLED_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include "fonts.h"

#define OLED_I2C_ADDR    (0x3C << 1)
#define OLED_WIDTH       128
#define OLED_HEIGHT      64

extern I2C_HandleTypeDef hi2c1;

/* Basic control */
void OLED_Init(void);
void OLED_Clear(void);
void OLED_UpdateScreen(void);
void OLED_Fill(uint8_t color);
void OLED_DisplayOn(void);
void OLED_DisplayOff(void);
void OLED_SetContrast(uint8_t value);
void OLED_Invert(uint8_t invert);

/* Text output */
void OLED_SetCursor(uint8_t x, uint8_t y);
void OLED_WriteChar(char ch, const FontDef *font, uint8_t color);
void OLED_WriteString(const char *str, const FontDef *font, uint8_t color);

#ifdef __cplusplus
}
#endif

#endif /* __OLED_H__ */