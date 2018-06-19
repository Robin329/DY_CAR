
/* DriverLib Includes */
#include <ti/devices/msp432e4/driverlib/driverlib.h>
/* Standard Includes */
#include <common.h>


uint32_t g_ui32SysClock;

int main(void)
{
  /* Configure the system clock for 16 MHz */
    g_ui32SysClock = MAP_SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN |
                                          SYSCTL_USE_PLL | SYSCTL_CFG_VCO_480),
                                          16000000);

   
    GPIOE_INIT();
    GPT_init();
    IncPIDInit();
    PWM_init(pwm_set,0,pwm_set,0);
 //   uart_init();
    QEIInit();
    
     
    
   

    while(1)
    {
        
    }
}
//void QEI0_IRQHandler(void)
//{
//    
//    int i;
//    int s;
//    int d;
//    unsigned long  COUNT = 0;
//    unsigned long  POS = 0;  
//    
//
//     
//    QEIIntClear(QEI0_BASE, QEI_INTTIMER);
//    POS = QEIPositionGet(QEI0_BASE);
//    d = QEIDirectionGet(QEI0_BASE);
//    
//    COUNT = QEIVelocityGet(QEI0_BASE);
//    s = (COUNT*6000)/2024;
//    i = IncPIDCalc(s);
//    printf("%d,%d\n",s,i);
//   // printf("The Speed is %d .Velocity is %d.Direction is %d.\n",s,COUNT,d);
//  // printf("%d\n",s);
//  
//    COUNT = 0;
//}