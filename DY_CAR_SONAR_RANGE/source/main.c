/******************************************************************************
 * MSP432E401Y
 * Description:通过蓝牙控制小车行走并进行测距
 * Author: Robin.J
***************************************************************************/
/* DriverLib Includes */
#include <ti/devices/msp432e4/driverlib/driverlib.h>
#include <common.h>
#include <qei.h>
uint32_t g_ui32SysClock;

int main(void)
{
  /* Configure the system clock for 16 MHz */
    g_ui32SysClock = MAP_SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN |
                                          SYSCTL_USE_PLL | SYSCTL_CFG_VCO_480),
                                          16000000);
    GPT_init();      //定时器初始化
    Timer_init();
    IncPIDInit();       //PID函数初始化
    PWM_init(pwm_set,0,pwm_set,0);//PWM初始化
    uart_init();        //串口初始化
    QEIInit();          //QEI初始化
    
    while(1)
    {
        Sonar_Gen();
    }
}

/******************* (C) COPYRIGHT 2018 DY EleTe *****END OF FILE************/