#include "oled.h"
#include "i2c.h"
#include <string.h>

#define CTRL_CMD    0x80
#define CTRL_DATA   0x40
#define I2C_TIMEOUT 100
#define PAGES       8

static uint8_t Buf[OLED_WIDTH * PAGES];
static uint8_t Cx = 0, Cy = 0;

/* ?? Low-level I2C ?? */

void OLED_WriteCommand(uint8_t cmd)
{
    uint8_t d[2] = {CTRL_CMD, cmd};
    HAL_I2C_Master_Transmit(&hi2c1, OLED_I2C_ADDR, d, 2, I2C_TIMEOUT);
}

static void WritePage(uint8_t page)
{
    OLED_WriteCommand(0xB0 | page);
    OLED_WriteCommand(0x00);
    OLED_WriteCommand(0x10);

    uint8_t d[OLED_WIDTH + 1];
    d[0] = CTRL_DATA;
    memcpy(d + 1, &Buf[page * OLED_WIDTH], OLED_WIDTH);
    HAL_I2C_Master_Transmit(&hi2c1, OLED_I2C_ADDR, d, OLED_WIDTH + 1, I2C_TIMEOUT);
}

/* ?? Display control ?? */

void OLED_Init(void)
{
    HAL_Delay(100);

    static const uint8_t cmds[] = {
        0xAE, 0xD5, 0x80, 0xA8, 0x3F, 0xD3, 0x00, 0x40,
        0x8D, 0x14, 0x20, 0x02, 0xA1, 0xC8, 0xDA, 0x12,
        0x81, 0x7F, 0xD9, 0xF1, 0xDB, 0x40, 0xA4, 0xA6,
        0x2E, 0xAF
    };
    for (uint32_t i = 0; i < sizeof(cmds); i++)
        OLED_WriteCommand(cmds[i]);

    OLED_Clear();
}

void OLED_Clear(void)
{
    memset(Buf, 0, sizeof(Buf));
    OLED_UpdateScreen();
}

void OLED_Fill(uint8_t color)
{
    memset(Buf, color ? 0xFF : 0x00, sizeof(Buf));
}

void OLED_UpdateScreen(void)
{
    for (uint8_t p = 0; p < PAGES; p++)
        WritePage(p);
}

void OLED_SetContrast(uint8_t v)
{
    OLED_WriteCommand(0x81);
    OLED_WriteCommand(v);
}

void OLED_DisplayOn(void)  { OLED_WriteCommand(0xAF); }
void OLED_DisplayOff(void) { OLED_WriteCommand(0xAE); }
void OLED_Invert(uint8_t i){ OLED_WriteCommand(i ? 0xA7 : 0xA6); }

/* ?? Cursor ?? */

void OLED_SetCursor(uint8_t x, uint8_t y)
{
    Cx = x;
    Cy = y;
}

/* ?? Text rendering (row-major fonts only) ?? */

void OLED_WriteChar(char ch, const FontDef *font, uint8_t color)
{
    if (ch < font->startChar || ch > font->endChar) return;

    uint16_t idx = (uint16_t)(ch - font->startChar) * font->charHeight;
    for (uint8_t row = 0; row < font->charHeight; row++) {
        uint8_t d = font->data[idx + row];
        for (uint8_t col = 0; col < font->charWidth; col++) {
            uint8_t px = Cx + col;
            uint8_t py = Cy + row;
            if (px >= OLED_WIDTH || py >= OLED_HEIGHT) continue;
            uint8_t on = (d >> (7 - col)) & 1;
            if (!color) on = !on;
            uint32_t bi = px + (py >> 3) * OLED_WIDTH;
            if (on) Buf[bi] |=  (1 << (py & 7));
            else    Buf[bi] &= ~(1 << (py & 7));
        }
    }

    Cx += font->charWidth;
    if (Cx + font->charWidth > OLED_WIDTH) {
        Cx = 0;
        Cy += font->charHeight;
    }
}

void OLED_WriteString(const char *str, const FontDef *font, uint8_t color)
{
    while (*str) OLED_WriteChar(*str++, font, color);
    OLED_UpdateScreen();
}