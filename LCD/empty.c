#include "ti/devices/msp/m0p/mspm0g350x.h"
#include "ti/driverlib/m0p/dl_core.h"
#include "ti_msp_dl_config.h"
#include "stdint.h"
#include "lcdlib/LCDM0.h"
/*
Basic code for the 16x2 Liquid crystal display, you need to include/create the "lcdlib" folder in the project and add both LCDM0.c and LCDM0.h files. 
You do not need to initialize GPIOB pins, theyre already setup in the LCDM0.c file.
The LCDM0.c and LCDM0.h files are designed for the most basic and universal way for the majority of the MSPM0 microcontrollers.
If you need to change the pins you can easily change the layouts under LCDM0.c and its GPIOB peripherals.
If you decide to change pins note UART,ADC and I2c pins need to be dissabled then turned to output pins.
#define delay(ms)    DL_Common_delayCycles(32000 * ms) // 32 MHz clock to ms
Setup:
LCD_Initialize();

Functions:
LCD_Clear();
LCD_Print(char* text, uint8_t column, uint8_t row); 
Display_On();
Display_Off();
Cursor_On();
Cursor_Off();
Blink_Cursor();
delay(); in ms

*/
int main(void)
{

    LCD_Initialize(); 
    Display_On();
    delay(2000);
    
    while (1) 
    {        
        LCD_Print("Hello!", 0, 0);
        delay(1000);
    }
}
