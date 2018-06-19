/******************************************************************************
 * MSP432E401Y
 * Description:本函数实现定时和测速功能  
 * 引脚：PA4->编码器输入信号
 *        
 * Author: Robin.J
***************************************************************************/

/* DriverLib Includes */
#include <ti/devices/msp432e4/driverlib/driverlib.h>
/* Standard Includes */
#include <common.h>

uint32_t count = 0;     //编码器脉冲总数
//uint32_t count1 = 0;
//uint32_t count2 = 0;

uint32_t CNT1 = 0;      //100ms时编码器脉冲数
uint32_t CNT2 = 0;      //200ms时编码器脉冲数
int speed = 0;  //转速（rpm/min）
uint32_t time1 = 0;     //计时10ms增1

void TIMER2A_IRQHandler(void)
{
    uint32_t getTimerInterrupt;

    count++;//脉冲计数
//    count1 = MAP_TimerValueGet(TIMER2_BASE,TIMER_B);
//    count2 = MAP_TimerLoadGet(TIMER2_BASE,TIMER_B);/
    getTimerInterrupt = MAP_TimerIntStatus(TIMER2_BASE, true);
    MAP_TimerIntClear(TIMER2_BASE, getTimerInterrupt);
}

void TIMER1A_IRQHandler(void)
{
    uint32_t getTimerInterrupt;

//    CNT1 = count;
//    CNT2 = CNT1;
//    speed = ((CNT1 - CNT2)/506) * 6000;
//    count = 0;
 
    time1++;//计时，每10ms增1
    if(time1 == 10){  
      CNT1 = count;
    }if(time1 == 20){
      
      CNT2 = count;
      //count1 = CNT2 -  CNT1;
      speed = (int)(((CNT2 - CNT1)/506.0) * 600);
      //count = 0;
      time1 = 0;
      count = 0;
    }  
    
    /* Get timer interrupt status  and clear the same */
    getTimerInterrupt = MAP_TimerIntStatus(TIMER1_BASE, true);
    MAP_TimerIntClear(TIMER1_BASE, getTimerInterrupt);

}


void GPT_init(void)
{

    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

        while(!(SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA)))
    {
    }
    MAP_GPIOPinConfigure(GPIO_PA4_T2CCP0);
    MAP_GPIOPinTypeTimer(GPIO_PORTA_BASE, GPIO_PIN_4);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER2);
    while(!(SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER2)))
    {
    }
     MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
    while(!(SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER1)))
    {
    }
    
    MAP_TimerConfigure(TIMER2_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_A_CAP_TIME_UP);
    MAP_TimerIntEnable(TIMER2_BASE, TIMER_CAPA_EVENT);
    MAP_TimerControlEvent(TIMER2_BASE, TIMER_A, TIMER_EVENT_POS_EDGE);
      
    MAP_TimerConfigure(TIMER1_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_A_PERIODIC);
    MAP_TimerIntEnable(TIMER1_BASE, TIMER_TIMA_TIMEOUT);
    
    /* Since the 16-bit timer can count only 65536 value, we use the pre
     * scaler of 256 to divide down the count rate by 256. Thus the actual
     * count load is16e6/256 = 62500. Now when to count at 0.1 sec the
     * load value in the timer would be 62500 * 0.1 =6250. */
    MAP_TimerPrescaleSet(TIMER1_BASE, TIMER_A, 255);
    MAP_TimerLoadSet(TIMER1_BASE, TIMER_A, 625);//10ms
    /* Enable Timer Interrupt */
    MAP_IntEnable(INT_TIMER2A); 
    MAP_IntEnable(INT_TIMER1A);
    /* Enable the timer count */
    MAP_TimerEnable(TIMER2_BASE, TIMER_A);    
    MAP_TimerEnable(TIMER1_BASE, TIMER_A);

}

/******************* (C) COPYRIGHT 2018 DY EleTe *****END OF FILE************/