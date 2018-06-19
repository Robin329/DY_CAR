#ifndef _PID_H
#define _PID_H


//定义PID控制结构体
typedef struct 
{
	float SetPoint_l;
	float SetPoint_r;
        
	float Proportion_r;       //比例常数Proportional Const
	float Integral_r;         //积分常数Integral Const
	float Derivative_r;       //微分常数Derivative Const
        
        float Proportion_l;       //比例常数Proportional Const
	float Integral_l;         //积分常数Integral Const
	float Derivative_l;       //微分常数Derivative Const
	
	float iError_l;     //当前误差
	float iIncpid_l;    //PID返回值
        
        float iError_r;     //当前误差
	float iIncpid_r;    //PID返回值
        
//        	int iError;     //当前误差
//	int iIncpid;    //PID返回值
	
        float A_r;
        float B_r;
        float C_r;
        
        float A_l;
        float B_l;
        float C_l;
	float LastError_l;  //Error[-1]
	float PrevError_l;  //Error[-2]
        
        float LastError_r;  //Error[-1]
	float PrevError_r;  //Error[-2]
        
        float limit;
        
	
}PID;
//



//声明PID实体
static PID sPID;
static PID *sptr = &sPID;


extern void IncPIDInit(void);
extern float IncPIDCalc_l(float NextPoint);
extern float IncPIDCalc_r(float NextPoint);

#endif