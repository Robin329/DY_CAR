#ifndef _PID_H
#define _PID_H


//定义PID控制结构体
typedef struct 
{
	float SetPoint;
	
	float Proportion;       //比例常数Proportional Const
	float Integral;         //积分常数Integral Const
	float Derivative;       //微分常数Derivative Const
	
	float iError;     //当前误差
	float iIncpid;    //PID返回值
        
//        	int iError;     //当前误差
//	int iIncpid;    //PID返回值
	
        float A;
        float B;
        float C;
	float LastError;  //Error[-1]
	float PrevError;  //Error[-2]
        
        float limit;
        
	
}PID;
//



//声明PID实体
static PID sPID;
static PID *sptr = &sPID;


extern void IncPIDInit(void);
extern float IncPIDCalc(float NextPoint);

#endif