/******************************************************************************
 * MSP432E401Y
 * Description:³¬Éù²¨²â¾à¹¦ÄÜ
 * Author: Robin.J
*******************************************************************************/
#ifndef _SONAR_H
#define _SONAR_H

#include <stdint.h>
extern uint32_t systemClock;
extern void Timer_init(void);
extern float Distance(float time);
extern void Sonar_Gen(void);
extern void Delay_ms(uint16_t n);
extern void Delay_us(uint16_t n);
#endif
/******************* (C) COPYRIGHT 2018 DY EleTe *****END OF FILE************/