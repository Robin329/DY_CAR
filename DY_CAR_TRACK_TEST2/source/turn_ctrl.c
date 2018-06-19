
/* DriverLib Includes */
#include <ti/devices/msp432e4/driverlib/driverlib.h>
#include <common.h>

int ch_l,ch_r;

void Delay_ms(uint8_t n)
{

  SysCtlDelay((g_ui32SysClock / (1000 * 3)) * n);//delay n ms

}
//ch_l = 30,10,5
void Forward(void)
{
  
  ch_l = 80;
  ch_r = 80;

}
void Turn_Left_Circle(void)//左原地转
{
  ch_l = 80;
  ch_r = 80;
}
void Turn_Spin_Left(void)//左大转
{
  ch_l = 20;
  ch_r = 80;

}
void Turn_Left(void)//差速左小转
{

  ch_l = 60;
  ch_r = 80;
  
}
void Turn_Right_Circle(void)//右原地转
{
  ch_l = 80;
  ch_r = 80;
}
void Turn_Spin_Right(void)//右大转
{
  ch_l = 80;
  ch_r = 20;
}
void Turn_Right(void)//差速右小转
{

  ch_l = 80;
  ch_r = 60;

}

void Back(void)//倒退
{
  ch_l = 30;
  ch_r = 30;
}

void Stop(void)//停止
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
      PWM_init(0 ,pwm_pidl, 0, pwm_pidr);
      break;
    case 3 ://左转
      Turn_Left();
      PWM_init(pwm_pidl, 0 , pwm_pidr , 0);
      break;
    case 4 ://左大转
      Turn_Spin_Left();
      PWM_init(pwm_pidl, 0, pwm_pidr , 0);
      break;
    case 5 ://右大转
      Turn_Spin_Right();
      PWM_init(pwm_pidl, 0 ,  pwm_pidr,0);
      break;
    case 6 ://右转
      Turn_Right();
      PWM_init(pwm_pidl, 0 , pwm_pidr , 0);
      break;
    case 7 :
      Turn_Right_Circle();//右原地转圈
      PWM_init(pwm_pidl, 0 , 0 , pwm_pidr);
      break;
    case 8 :
      Turn_Left_Circle();//左原地转圈
      PWM_init( 0 ,pwm_pidl , pwm_pidr , 0);
      break;
    case 9 ://停止
      Stop();
      PWM_init(0, 0 , 0 , 0);
      break;
    default:
      break;
      
  }
}