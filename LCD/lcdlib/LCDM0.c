#include "ti/devices/msp/m0p/mspm0g350x.h"
#include "ti/driverlib/m0p/dl_core.h"
#include "ti_msp_dl_config.h"
#include "lcdlib/LCDM0.h"
#include "stdint.h"
#include "math.h"

void LCD_Initialize(void)
{
    GPIOB->GPRCM.RSTCTL = 0xB1000003;
    GPIOB->GPRCM.PWREN = 0x26000001;
    delay(110);
    
//Data Pins 
    IOMUX->SECCFG.PINCM[11] = 0x81; //      D4 |PB0 ANALOG INPUT, SPI CS
    IOMUX->SECCFG.PINCM[12] = 0x81; //      D5 |PB1 PWM
    IOMUX->SECCFG.PINCM[14] = 0x81; //      D6 |PB2 TA2CK ACLK, I2C SCL
    IOMUX->SECCFG.PINCM[15] = 0x81; //      D7 |PB3 RTCCLK  MCLK, I2C SDA

    IOMUX->SECCFG.PINCM[22] = 0x81; //      Register Select |PB6 SPI CS
    IOMUX->SECCFG.PINCM[23] = 0x81; //      Enable |PB7 SPI POCI

// Setup pins D4, D5, D6, D7, RS, EN as output
    GPIOB->DOE31_0 |= LCD_MASK; 

    GPIOB->DOUT31_0 = 0x03;

    for(int start=0; start <=3; start++)
    {
        LCD_Toggle();
        delay(5); 
    }
//switch to 4-bit
    GPIOB->DOUT31_0 = 0x02; 
    LCD_Toggle();
    delay(5);

    int status_LCD[]={0x28, 0x08,0x01,0x06,0x0c};
    for (int i = 0; i < 5; i++)
    {
        LCD_CMD(status_LCD[i]);
    }
    // LCDWriteCMD(0x28); //4-bit, 2 line, 5x8
    // LCDWriteCMD(0x08); // Instruction Flow
    // LCDWriteCMD(0x01); // Clear LCD
    // LCDWriteCMD(0x06); // Auto-Increment
    // LCDWriteCMD(0x0C); // Display, No Blink
 
}

static void LCD_Toggle(void)
{
    GPIOB->DOUT31_0 |= LCD_EN;
    GPIOB->DOUT31_0 &= ~LCD_EN;
}

static void LCD_CMD(unsigned char cmd) //writecmd
{
    GPIOB->DOUT31_0 &= ~LCD_RS;
    LowerNibble(cmd >> 4); 
    LCD_Toggle();
    LowerNibble(cmd);
    LCD_Toggle();
    delay(5); 
}

static void LCD_Write_Bits(unsigned char data) //writedata
{
    GPIOB->DOUT31_0 |= LCD_RS; //Set the RS to Data
    LowerNibble(data >> 4); //Upper Nibble
    LCD_Toggle();
    LowerNibble(data);
    LCD_Toggle();
    delay(5);
}

void LCD_Print(char* text, uint8_t column, uint8_t row)
{
    uint32_t i=0 ;
    if(column < 16)
    {
        column |= 0x80;          // Set the LCD for first line write
        switch (row) 
        {
            case 1:column |= 0x40;  break;// Set the LCD for second line write
            case 2:column |= 0x60;  break;// Set the LCD for first line write revers
            case 3:column |= 0x20;  break;// Set the LCD for second line write reverse
        }
        LCD_CMD(column);
    }
    while(text[i] != '\0')
    {
        LCD_Write_Bits(text[i]);
        i++;
    }
}

void LCD_Clear(void)
{
    LCD_CMD(0X01);
}
void Display_On(void)
{
    LCD_CMD(0X0C);
}
void Display_Off(void)
{
    LCD_CMD(0X08);
}
void Cursor_On(void)
{
    LCD_CMD(0X0E);
}
void Cursor_Off(void)
{
    LCD_CMD(0X0C);
}
void Blink_Cursor(void)
{
    LCD_CMD(0x0F);
}
