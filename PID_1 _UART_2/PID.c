#include <PID.h>
#include "ti/devices/msp432e4/driverlib/driverlib.h"
#include <ti/devices/msp432e4/driverlib/pwm.h>


float iError , iIncpid; //当前误差
float variable;

extern float ch;
//PID初始化
void IncPIDInit(void)
{
	sptr->SetPoint	= 80.0;		//设定值

	sptr->LastError = 0;		//前1次误差值
	sptr->PrevError = 0;		//前2次误差值

	sptr->Proportion = 0.8;		//比例
	sptr->Integral	 = 0.15;		//积分
	sptr->Derivative = 0.0;		//微分
        
        sptr->A = sptr->Proportion + sptr->Integral + sptr->Derivative;
        sptr->B = -(2*sptr->Derivative + sptr->Proportion);
        sptr->C = sptr->Derivative;

	sptr->iError = 0;			//当前误差
	sptr->iIncpid=0;			//增量误差
        
        sptr->limit = 49;

}

float IncPIDCalc(float NextPoint)
{
//   int iError , iIncpid ; //当前误差
  if(ch != 0){
    sptr->SetPoint = ch;
  }
    iError = sptr->SetPoint - NextPoint; //增量计算

   sptr->iIncpid =(int)(sptr->A * iError //E[k]项
             + sptr->B * sptr->LastError //E[k－1]项
             + sptr->C * sptr->PrevError); //E[k－2]项
//       iIncpid = sptr->Proportion * iError //E[k]项
//             - sptr->Integral * sptr->LastError //E[k－1]项
//             + sptr->Derivative * sptr->PrevError; //E[k－2]项
    
   variable =iError -  sptr->LastError;
   
    sptr->PrevError = sptr->LastError;   //存储误差，用于下次计算
    sptr->LastError = iError;
//	MAP_PWMPulseWidthSet(PWM0_BASE, PWM_OUT_2,
//                     MAP_PWMGenPeriodGet(PWM0_BASE, PWM_GEN_1)/4);
    
/*PWM limiting function, PWM value is 80, minimum is 0
*/
//    if(sptr->iIncpid  >= 0)
//    {
//      if(sptr->iIncpid <= sptr->limit){
//        
//        sptr->iIncpid += (pwm_set*100);
//      }
//      else{
//        sptr->iIncpid = (int)(sptr->limit + pwm_set * 100);
//      }
//    }
//    else if(sptr->iIncpid < 0){
//      
//            if(sptr->iIncpid >= -sptr->limit){
//        
//               sptr->iIncpid += (pwm_set*100);
//              }
//            else{
//            
//              sptr->iIncpid =(int)(pwm_set-sptr->limit);
//            }
//      
//    }
    
        if(sptr->iIncpid >= sptr->limit)
    {
      sptr->iIncpid = sptr->limit;
    
      }
      else if(sptr->iIncpid < -sptr->limit){
        
        sptr->iIncpid = -sptr->limit;
      }
    
      
  return(sptr->iIncpid);                         //返回增量值
    
}
