/******************************************************************************
 * MSP432E401Y
 * Description:QEI模块初始化  
 * 引脚：PL1->编码器输入信号1
 *       PL2->编码器输入信号2
 * Author: Robin.J
*******************************************************************************/

//QEI0初始化
/* DriverLib Includes */
#include <ti/devices/msp432e4/driverlib/driverlib.h>
/* Standard Includes */
#include <common.h>


    float pid_l = 0;        //左轮PID
    float pid_r = 0;        //右轮PID
    float s_l = 0;      //左轮当前速度值
    float s_r = 0;      //右轮当前速度值
//    uint8_t d;        //转动方向
    unsigned long  COUNT = 0;
//    unsigned long  POS = 0;   //计数位置
    
    uint8_t Num = 0;    //计时10ms增1
    float pwm_pidl = 0.5;
    float pwm_pidr = 0.5;

void QEIInit (void)
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

}

void QEI0_IRQHandler(void)
{
      Num++;    
    QEIIntClear(QEI0_BASE, QEI_INTTIMER);
//    POS = QEIPositionGet(QEI0_BASE);
//    d = QEIDirectionGet(QEI0_BASE);
  
    COUNT = QEIVelocityGet(QEI0_BASE);
    s_l = (COUNT*6000)/2024;    //左轮速度计算（rpm/min）
    s_r = speed;        //右轮速度
    
/* 左轮PID控制PWM占空比*/
    pid_l = IncPIDCalc_l(s_l);  // 返回左轮PID增量值
    pid_l *= 0.01;
     if(pid_l == -0.5){
      pwm_pidl = 0;     //当速度为0时PWM占空比为0
    }else{
    pwm_pidl += pid_l;
    }   
/* 右轮PID控制PWM占空比*/    
    
    pid_r = IncPIDCalc_r(s_r);  // 返回右轮PID增量值
    pid_r *= 0.01;
    if(pid_r == -0.5){
      pwm_pidr = 0;
    }else{
    pwm_pidr += pid_r;
    }
    
    
    if(pwm_pidl > 0.99){        // 限幅处理
    
    pwm_pidl = 0.99;
    
    } 
    if(pwm_pidr > 0.99){
      
      pwm_pidr = 0.99;
      
    }
      
    ControlCar(ch);     //蓝牙控制
  
//    UARTSend((uint8_t *)"Current Speed: ", 16);

if(!UARTBusy(UART0_BASE))       //串口发送数据
{
  if(Num == 50)
    {
//      UARTSend((uint8_t *)" Current:", 10);//10 is Decimal
      UARTSend((uint8_t *)" dis:", 10);
      Float2Char(dis,Buffer_Out);
      
//      sprintf(Buffer_Out,"%d",(int)s_r);
//      sprintf(Buffer_Out,"%d",(int)s_l);
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
/******************* (C) COPYRIGHT 2018 DY EleTe *****END OF FILE************/
