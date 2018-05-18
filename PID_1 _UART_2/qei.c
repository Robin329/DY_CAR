//********************************************************************
//QEI0初始化
/* DriverLib Includes */
#include <ti/devices/msp432e4/driverlib/driverlib.h>

/* Standard Includes */
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <PID.h>
#include <ti/devices/msp432e4/driverlib/uart.h>

    float pid;
    float s = 0;
    uint8_t d;
    unsigned long  COUNT = 0;
    unsigned long  POS = 0;  
    
    uint8_t Num = 0; 
    float pwm_pid = 0.5;
extern char Buffer[3]; 
extern char Buffer_Out[3]; 


void
QEIInit (void)
{
  
     MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_QEI0);//使能QEI0外设
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOL);/*enable L port*/
    MAP_IntEnable(INT_GPIOL);
    
    GPIOPinConfigure(GPIO_PL1_PHA0);
    GPIOPinConfigure(GPIO_PL2_PHB0);
    
    
    QEIEnable(QEI0_BASE);//使能正交编码器QEI0
    QEIConfigure(QEI0_BASE,(QEI_CONFIG_CAPTURE_A_B |QEI_CONFIG_NO_RESET|
    QEI_CONFIG_QUADRATURE|QEI_CONFIG_NO_SWAP),10000000);//使用A,B通道共4个边沿计算位置
    
//    GPIOPadConfigSet(GPIO_PORTL_BASE, GPIO_PIN_1,
//    GPIO_STRENGTH_4MA,
//    GPIO_PIN_TYPE_STD);
//    
//    GPIOPadConfigSet(GPIO_PORTL_BASE, GPIO_PIN_2,
//    GPIO_STRENGTH_4MA,
//    GPIO_PIN_TYPE_STD);
//    
//    GPIOPadConfigSet(GPIO_PORTL_BASE, GPIO_PIN_3,
//    GPIO_STRENGTH_4MA,
//    GPIO_PIN_TYPE_STD);
//  
    GPIOPinTypeQEI(GPIO_PORTL_BASE,GPIO_PIN_1|GPIO_PIN_2);//配置PL1，PL2为PhA1，PhB1
    QEIVelocityConfigure(QEI0_BASE, QEI_VELDIV_1, 16000000/100);//10ms
    
    //使能速度计算，使能QEI
    QEIVelocityEnable(QEI0_BASE);
    QEIEnable(QEI0_BASE);

        //速度计时器计时完成时触发中断
    QEIIntEnable(QEI0_BASE,QEI_INTTIMER);
    IntEnable(INT_QEI0);

//    return(0); 
}

void QEI0_IRQHandler(void)
{

      Num++;
     
    QEIIntClear(QEI0_BASE, QEI_INTTIMER);
//    POS = QEIPositionGet(QEI0_BASE);
//    d = QEIDirectionGet(QEI0_BASE);
    
    
    COUNT = QEIVelocityGet(QEI0_BASE);
    s = (COUNT*6000)/2024;
    


    pid = IncPIDCalc(s);
    pid *= 0.01;
    pwm_pid += pid;
    
    
    if(pwm_pid > 0.99){
   
      pwm_pid = 0.99;
      PWM_init(pwm_pid);
      
    }
    else{
      PWM_init(pwm_pid);
    }

    
    
//    UARTSend((uint8_t *)"Current Speed: ", 16);

if(!UARTBusy(UART0_BASE))
{
  if(Num == 10)
    {
      UARTSend((uint8_t *)" Current:", 10);//10 is Decimal
      sprintf(Buffer_Out,"%d",(int)s);
      UARTSend((uint8_t *)Buffer_Out, 10);
      
      memset(Buffer_Out,0,sizeof(Buffer_Out));//Empty character array

      memset(Buffer,0,sizeof(Buffer));
      Num = 0;
    }
}
// printf("%d,%d\n",s,pid);
// printf("The Speed is %d .Velocity is %d.Direction is %d.\n",s,COUNT,d);
// printf("%d\n",s);
  
    COUNT = 0;
    
    
}
