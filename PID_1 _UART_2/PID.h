#ifndef _PID_H
#define _PID_H


//����PID���ƽṹ��
typedef struct 
{
	float SetPoint;
	
	float Proportion;       //��������Proportional Const
	float Integral;         //���ֳ���Integral Const
	float Derivative;       //΢�ֳ���Derivative Const
	
	float iError;     //��ǰ���
	float iIncpid;    //PID����ֵ
        
//        	int iError;     //��ǰ���
//	int iIncpid;    //PID����ֵ
	
        float A;
        float B;
        float C;
	float LastError;  //Error[-1]
	float PrevError;  //Error[-2]
        
        float limit;
        
	
}PID;
//



//����PIDʵ��
static PID sPID;
static PID *sptr = &sPID;


extern void IncPIDInit(void);
extern float IncPIDCalc(float NextPoint);

#endif