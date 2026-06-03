#ifndef LCDM0_H_
#define LCDM0_H_

#include "ti/devices/msp/m0p/mspm0g350x.h"
#include "ti/driverlib/m0p/dl_core.h"
#include "ti_msp_dl_config.h"
#include "stdint.h"

#define LCD_D4 (1<<0) //PB0
#define LCD_D5 (1<<1) //PB1
#define LCD_D6 (1<<2) //PB2
#define LCD_D7 (1<<3) //PB3
#define LCD_RS (1<<6) //PB6
#define LCD_EN (1<<7) //PB7

#define LCD_DATA ((LCD_D4) | (LCD_D5) | (LCD_D6) | (LCD_D7))
#define LCD_MASK ((LCD_DATA) | (LCD_RS) | (LCD_EN))

/* GPIO Operations */
#define LowerNibble(x)  GPIOB->DOUT31_0 = (GPIOB->DOUT31_0 & 0xF0) + (x & 0x0F)

/* Delay Macros (Assuming 32MHz Clock) */
#define delay(ms)    DL_Common_delayCycles(32000 * ms) // 32 MHz clock to ms

/* LCD Driver Function Prototypes */
void LCD_Initialize(void);
void LCD_Clear(void);
void LCD_Print(char* text, uint8_t column, uint8_t row);
void Display_On(void);
void Display_Off(void);
void Cursor_On(void);
void Cursor_Off(void);
void Blink_Cursor(void);

/* Internal Helper Functions */
static void LCD_Toggle(void);
static void LCD_CMD(unsigned char cmd);
static void LCD_Write_Bits(unsigned char data);

#endif /* LCDM0_H_ */