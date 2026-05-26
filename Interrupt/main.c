#include "ti/devices/msp/m0p/mspm0g350x.h"
#include "ti/driverlib/dl_common.h" // For DL_Common_delayCycles function
#include "stdio.h"
int x=0;
int main(void)
{ 
  // SET PINS
    GPIOA->GPRCM.RSTCTL = (0xB1 << 24) | (1 << 1) | (1 << 0); // unlock and write, Assert reset, Clear reset 				
    GPIOA->GPRCM.PWREN = (0x26 << 24) | (1 << 0);
    DL_Common_delayCycles(24);

   // LED
    IOMUX->SECCFG.PINCM[18] = (1<<7) | (1<<0); // PA8
    GPIOA->DOE31_0 |= (1 << 8);                   // set doe register to enable peripheral (1 means using mode 1 or GPIO)

    //BUTTON PA18
    IOMUX->SECCFG.PINCM[39] =(5 << 16) | (1 << 7)  |  (1 << 0); // PA22 PULLDOWN : 0x0005 means pulldown;

  // INTERRUPT
  GPIOA->POLARITY31_16 = (1<<4); // rising
  GPIOA->CPU_INT.ICLR = (1<<18);  // clear bit 18
  GPIOA->CPU_INT.IMASK = (1<<18); // arm PA18 (1<<18)
  
  NVIC->IP[0] = (NVIC->IP[0]&~(3<<6))|2<<6;  // clear bits, set priority (bits 15,14)
  NVIC->ISER[0] = 1 << 1;            // Group1 interrupt

   __enable_irq();

    while (1)
    {     
      GPIOA->DOUT31_0 |= (1 << 8); // LED ON
      printf("%d\n",x);
        x++;
        DL_Common_delayCycles(40000000); // 1/2 sec
    }
}
void GROUP1_IRQHandler(void)
{ 
if (GPIOA->CPU_INT.IIDX==19) // 
{
    GPIOA->DOUT31_0 &= ~(1 << 8); // LED OFF
    printf("paused\n");
    DL_Common_delayCycles(40000000); // 1/2 sec
    GPIOA->CPU_INT.ICLR = (1<<18); // clear bit 18

}
  
}
