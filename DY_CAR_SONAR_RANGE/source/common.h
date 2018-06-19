#ifndef _COMMON_
#define _COMMON_
/* Standard Includes */
#include <ti/devices/msp432e4/driverlib/driverlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <PID.h>
#include <turn_ctrl.h>
#include <gpt.h>
#include <pwm.h>
#include <Sonar.h>
#include <math.h>


extern unsigned char Buffer[5]; 
extern unsigned char Buffer_Out[5]; 
extern int speed;
extern unsigned char ch;
extern uint32_t g_ui32SysClock;
extern float s_l;
extern float s_r;

extern float pwm_pidl;
extern float pwm_pidr;
extern uint32_t g_ui32SysClock; 
extern float dis;

typedef unsigned char uint8;
typedef unsigned char uint32;


#endif