#include <PID.h>
#include "ti/devices/msp432e4/driverlib/driverlib.h"
#include <ti/devices/msp432e4/driverlib/pwm.h>


float iError , iIncpid; //��ǰ���
float variable;

extern float ch;
//PID��ʼ��
void IncPIDInit(void)
{
	sptr->SetPoint	= 80.0;		//�趨ֵ

	sptr->LastError = 0;		//ǰ1�����ֵ
	sptr->PrevError = 0;		//ǰ2�����ֵ

	sptr->Proportion = 0.8;		//����
	sptr->Integral	 = 0.15;		//����
	sptr->Derivative = 0.0;		//΢��
        
        sptr->A = sptr->Proportion + sptr->Integral + sptr->Derivative;
        sptr->B = -(2*sptr->Derivative + sptr->Proportion);
        sptr->C = sptr->Derivative;

	sptr->iError = 0;			//��ǰ���
	sptr->iIncpid=0;			//�������
        
        sptr->limit = 49;

}

float IncPIDCalc(float NextPoint)
{
//   int iError , iIncpid ; //��ǰ���
  if(ch != 0){
    sptr->SetPoint = ch;
  }
    iError = sptr->SetPoint - NextPoint; //��������

   sptr->iIncpid =(int)(sptr->A * iError //E[k]��
             + sptr->B * sptr->LastError //E[k��1]��
             + sptr->C * sptr->PrevError); //E[k��2]��
//       iIncpid = sptr->Proportion * iError //E[k]��
//             - sptr->Integral * sptr->LastError //E[k��1]��
//             + sptr->Derivative * sptr->PrevError; //E[k��2]��
    
   variable =iError -  sptr->LastError;
   
    sptr->PrevError = sptr->LastError;   //�洢�������´μ���
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
    
      
  return(sptr->iIncpid);                         //��������ֵ
    
}
