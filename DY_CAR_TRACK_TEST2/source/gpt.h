#ifndef _GPT_H
#define _GPT_H


extern float s_r;      //右轮当前速度值
extern    float pwm_pidl;
extern    float pwm_pidr;
extern  float pid_r;        //右轮PID

extern void GPT_init(void);

#endif