#ifndef _COMMON_
#define _COMMON_
/* Standard Includes */
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <PID.h>
#include <turn_ctrl.h>
#include <track.h>
#include <gpt.h>
#include <pwm.h>
#include <qei.h>

extern float pwm_pidl;
extern float pwm_pidr;
extern uint32_t g_ui32SysClock; 

extern char Buffer[3]; 
extern char Buffer_Out[3]; 
extern int speed;
extern unsigned char ch;


#endif