/******************************************************************************
 * MSP432E401Y
 * Description:超声波测距功能
 * 引脚:PM2->Trig
 *      PA5->Echo
 *      
 * Author: Robin.J
***************************************************************************/
/* DriverLib Includes */
#include <ti/devices/msp432e4/driverlib/driverlib.h>
#include <common.h>

uint32_t timer_cnt1;    //高电平时间开始
float timer_cnt2;       //高电平时间结束
uint32_t count1;        //捕获的计数值
float dis;              //距离(cm)
//volatile bool bSetEventFlag = 0;
//volatile bool flag = 1;
//int32_t Time_Count = 0;

void Delay_us(uint16_t n)
{

  SysCtlDelay((g_ui32SysClock / (1000000 * 3)) * n);//delay n ms

}

void Delay_ms(uint16_t n)
{

  SysCtlDelay((g_ui32SysClock / (1000 * 3)) * n);//delay n ms

}

void TIMER3A_IRQHandler(void)
{

    uint32_t getTimerIntStatus;
    /* Get the timer interrupt status and clear the same */
    getTimerIntStatus = MAP_TimerIntStatus(TIMER3_BASE, true);

    MAP_TimerIntClear(TIMER3_BASE, getTimerIntStatus);


//    if(bSetEventFlag){
//      Time_Count++;
//    }
}

void TIMER2B_IRQHandler(void)
{
    uint32_t getTimerIntStatus;
    
    static uint32_t temp_cnt1,temp_cnt1_2;
   // bSetEventFlag = 1;
    
    /* Get the timer interrupt status and clear the same */
    getTimerIntStatus = MAP_TimerIntStatus(TIMER2_BASE, true);

    MAP_TimerIntClear(TIMER2_BASE, getTimerIntStatus);
    
    
    count1 = MAP_TimerValueGet(TIMER2_BASE, TIMER_B);
//    count1 = Time_Count;
 
  if(MAP_GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_5))
  {
    MAP_TimerControlEvent(TIMER2_BASE, TIMER_B, TIMER_EVENT_NEG_EDGE);
    temp_cnt1 = count1;
  }
  else
  {
    MAP_TimerControlEvent(TIMER2_BASE, TIMER_B, TIMER_EVENT_POS_EDGE);
    temp_cnt1_2 = count1;
    
//    bSetEventFlag = 0;
//    Time_Count = 0;
    
    if(temp_cnt1_2 >= temp_cnt1)
    {
      timer_cnt1 = (temp_cnt1_2 - temp_cnt1);
      timer_cnt2 = timer_cnt1/16;//us.系统时钟为16MHz
    }
    else
    {
      timer_cnt1 = 16777215 - temp_cnt1 + temp_cnt1_2;//预分频之后能计数到1677216
      timer_cnt2 = timer_cnt1/16;
    }
  }
  
  dis = Distance(timer_cnt2);//计算距离
}



void Timer_init(void)
{
  
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOM);

    MAP_GPIOPinConfigure(GPIO_PA5_T2CCP1);
    //MAP_GPIOPinConfigure(GPIO_PM2_T3CCP0);
    
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER2);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER3);
    
    MAP_GPIOPinTypeGPIOOutput(GPIO_PORTM_BASE, GPIO_PIN_2);
    MAP_GPIOPinWrite(GPIO_PORTM_BASE, GPIO_PIN_2, ~(GPIO_PIN_2));

    MAP_GPIOPinTypeTimer(GPIO_PORTA_BASE, GPIO_PIN_5);
    //MAP_GPIOPinTypeTimer(GPIO_PORTM_BASE, GPIO_PIN_2);
    
    
    MAP_TimerConfigure(TIMER3_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_A_PERIODIC);
    MAP_TimerConfigure(TIMER2_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_B_CAP_TIME_UP);

    
    MAP_TimerIntEnable(TIMER2_BASE, TIMER_CAPB_EVENT);
    MAP_TimerIntEnable(TIMER3_BASE, TIMER_TIMA_TIMEOUT);
    MAP_TimerControlEvent(TIMER2_BASE, TIMER_B, TIMER_EVENT_POS_EDGE);
    /* 16000000/256 = 62500*/
    

    MAP_TimerPrescaleSet(TIMER2_BASE, TIMER_B, 255);//预分频
    MAP_TimerPrescaleSet(TIMER2_BASE, TIMER_B, 255);
//    MAP_TimerLoadSet(TIMER3_BASE, TIMER_A, 16000000/1000);//200khz
    
//    MAP_TimerMatchSet(TIMER3_BASE, TIMER_A,
//                   MAP_TimerLoadGet(TIMER3_BASE, TIMER_A) / 2);//输出的PWM占空比为25%
    

    MAP_TimerPrescaleSet(TIMER3_BASE, TIMER_A, 255);
    MAP_TimerLoadSet(TIMER3_BASE, TIMER_A, 3);//10us
    
    MAP_TimerEnable(TIMER3_BASE, TIMER_A);
    MAP_TimerEnable(TIMER2_BASE, TIMER_B);
    /* Enable the timer interrupt */
    MAP_IntEnable(INT_TIMER3A);
    MAP_IntEnable(INT_TIMER2B);
}


float Distance(float time)
{
  float distance = 0;
  distance = time/58.0;//time为us,计算公式为:distance = (time*(340m/s)/2)
  
  return distance;

}

void Sonar_Gen(void){

  MAP_GPIOPinWrite(GPIO_PORTM_BASE, GPIO_PIN_2, GPIO_PIN_2);
  Delay_us(20);//高电平的时间>=10us

  MAP_GPIOPinWrite(GPIO_PORTM_BASE, GPIO_PIN_2, ~(GPIO_PIN_2));
  Delay_ms(1);//低电平时间为1ms
  
}
/******************* (C) COPYRIGHT 2018 DY EleTe *****END OF FILE************/