/******************************************************************************
 * MSP432E401Y
 * Description:控制小车前进后退左右转弯停止 
 * ‘1’->前进
 * ‘2’->后退
 * ‘3’->左转
 * ‘4’->右转
 * ‘5’->停止  
 * 引脚：
 *        
 * Author: Robin.J
*******************************************************************************/
#include <common.h>
/* DriverLib Includes */
#include <ti/devices/msp432e4/driverlib/driverlib.h>

int ch_l,ch_r;

void Delay_ms(uint8_t n)
{

  SysCtlDelay((g_ui32SysClock / (1000 * 3)) * n);//delay n ms

}
void Forward()  //前进
{
  
  ch_l = 30;
  ch_r = 30;

}

void Turn_Left()  //左转
{

  ch_l = 10;
  ch_r = 30;
  
}

void Turn_Right()    //右转   
{

  ch_l = 30;
  ch_r = 10;

}

void Back()     //后退
{
  ch_l = 30;
  ch_r = 30;
}

void Stop()     //停止
{
  ch_l = 0;
  ch_r = 0;
}
void ControlCar(unsigned char ConType)
{ 
  switch(ConType)
  {
    case 1 ://前进
      Forward();
      PWM_init(pwm_pidl, 0 , pwm_pidr , 0 );
      break;
    case 2 ://后退
      Back();
      PWM_init(0 ,pwm_pidl,  0, pwm_pidr);
      break;
    case 3 ://左转
      Turn_Left();
      PWM_init(0 ,pwm_pidl, pwm_pidr , 0);
      break;
    case 4 ://右转
      Turn_Right();
      PWM_init(pwm_pidl, 0 , 0 , pwm_pidr);
      break;
    case 5 ://停止
      Stop();
      PWM_init(0, 0 , 0 , 0);
      break;
    default:
      break;
      
  }
}

/******************* (C) COPYRIGHT 2018 DY EleTe *****END OF FILE************/