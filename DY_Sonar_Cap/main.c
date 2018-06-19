/******************************************************************************
 * MSP432E401Y
 * Description:³¬Éù²¨²â¾à¹¦ÄÜ
 * Author: Robin.J
*******************************************************************************/
/* DriverLib Includes */
#include <ti/devices/msp432e4/driverlib/driverlib.h>
/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <Sonar.h>
uint32_t systemClock;

int main(void)
{
    /* Configure the system clock for 16 MHz */
    systemClock = MAP_SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN |
                                          SYSCTL_USE_PLL | SYSCTL_CFG_VCO_480),
                                          16000000);
    Timer_init();   
  while(1){

    Sonar_Gen();
  }
  
}
/******************* (C) COPYRIGHT 2018 DY EleTe *****END OF FILE************/